// this tool fixes the path of the pdb inside the dll
// this code was copied and adapted from http://www.debuginfo.com/examples/debugdir.html

#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include <crtdbg.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#pragma comment(lib, "Shlwapi.lib")

#define MakePtr(cast, ptr, addValue) (cast)((DWORD_PTR)(ptr) + (DWORD_PTR)(addValue))
#define CV_SIGNATURE_NB10 '01BN'
#define CV_SIGNATURE_RSDS 'SDSR'

struct CV_HEADER {
  DWORD CvSignature;
  LONG Offset;
};

struct CV_INFO_PDB20 {
  struct CV_HEADER Header;
  DWORD Signature;
  DWORD Age;      
  BYTE PdbFileName[1];
};

struct CV_INFO_PDB70 {
  DWORD CvSignature;
  GUID Signature;
  DWORD Age;           
  BYTE PdbFileName[1]; 
};

LPCTSTR ProcessCmdLine(int argc, TCHAR* argv[]);
bool CheckDosHeader(PIMAGE_DOS_HEADER pDosHeader);
bool CheckNtHeaders(PIMAGE_NT_HEADERS pNtHeaders);
bool CheckSectionHeaders(PIMAGE_NT_HEADERS pNtHeaders);
bool CheckDebugDirectory(PIMAGE_DEBUG_DIRECTORY pDebugDir, DWORD DebugDirSize);
bool IsPE32Plus(PIMAGE_OPTIONAL_HEADER pOptionalHeader, bool* bPE32Plus);
bool GetDebugDirectoryRVA(PIMAGE_OPTIONAL_HEADER pOptionalHeader,
                          DWORD* DebugDirRva,
                          DWORD* DebugDirSize);
bool GetFileOffsetFromRVA(PIMAGE_NT_HEADERS pNtHeaders, DWORD Rva, DWORD* FileOffset);
void
DumpDebugDirectoryEntries(LPBYTE pImageBase, PIMAGE_DEBUG_DIRECTORY pDebugDir, DWORD DebugDirSize);
void DumpDebugDirectoryEntry(LPBYTE pImageBase, PIMAGE_DEBUG_DIRECTORY pDebugDir);
void DumpCodeViewDebugInfo(LPBYTE pDebugInfo, DWORD DebugInfoSize);
void DumpMiscDebugInfo(LPBYTE pDebugInfo, DWORD DebugInfoSize);
LPCTSTR DebugTypeToStr(DWORD DebugType);
void DumpGuid(GUID Guid);

int
main(int argc, char* argv[]) {

  wchar_t FileName[MAX_FILE_NAME_LENGTH] = {0};
  mbstowcs(FileName, argv[1],  MAX_FILE_NAME_LENGTH);

  if (FileName == 0)
    return 0;

  HANDLE hFile = NULL;
  HANDLE hFileMap = NULL;
  LPVOID lpFileMem = 0;

  do {
    
    hFile = CreateFile(
        FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile == INVALID_HANDLE_VALUE) || (hFile == NULL)) {
      _tprintf(_T("Error: Cannot open the file. Error code: %u \n"), GetLastError());
      break;
    }

    hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);

    if (hFileMap == NULL) {
      _tprintf(_T("Error: Cannot open the file mapping object. Error code: %u \n"), GetLastError());
      break;
    }

    lpFileMem = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    if (lpFileMem == 0) {
      _tprintf(_T("Error: Cannot map the file. Error code: %u \n"), GetLastError());
      break;
    }

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpFileMem;

    if (!CheckDosHeader(pDosHeader)) {
      _tprintf(_T("Error: File is not a PE executable.\n"));
      break;
    }

    PIMAGE_NT_HEADERS pNtHeaders = MakePtr(PIMAGE_NT_HEADERS, pDosHeader, pDosHeader->e_lfanew);

    if (!CheckNtHeaders(pNtHeaders)) {
      _tprintf(_T("Error: File is not a PE executable.\n"));
      break;
    }

    if (!CheckSectionHeaders(pNtHeaders)) {
      _tprintf(_T("Error: File is not a PE executable.\n"));
      break;
    }

    DWORD DebugDirRva = 0;
    DWORD DebugDirSize = 0;

    if (!GetDebugDirectoryRVA(&pNtHeaders->OptionalHeader, &DebugDirRva, &DebugDirSize)) {
      _tprintf(_T("Error: File is not a PE executable.\n"));
      break;
    }

    if ((DebugDirRva == 0) || (DebugDirSize == 0)) {
      _tprintf(_T("Debug directory not found.\n"));
      break;
    }

    DWORD DebugDirOffset = 0;

    if (!GetFileOffsetFromRVA(pNtHeaders, DebugDirRva, &DebugDirOffset)) {
      _tprintf(_T("Debug directory not found.\n"));
      break;
    }

    PIMAGE_DEBUG_DIRECTORY pDebugDir = MakePtr(PIMAGE_DEBUG_DIRECTORY, lpFileMem, DebugDirOffset);

    if (!CheckDebugDirectory(pDebugDir, DebugDirSize)) {
      _tprintf(_T("Error: Debug directory is not valid.\n"));
      break;
    }

    DumpDebugDirectoryEntries((LPBYTE)lpFileMem, pDebugDir, DebugDirSize);

  } while (0);

  if (lpFileMem != 0) {
    if (!UnmapViewOfFile(lpFileMem)) {
      _tprintf(_T("Error: Cannot unmap the file. Error code: %u \n"), GetLastError());
      _ASSERT(0);
    }
  }

  if (hFileMap != NULL) {
    if (!CloseHandle(hFileMap)) {
      _tprintf(_T("Error: Cannot close the file mapping object. Error code: %u \n"),
               GetLastError());
      _ASSERT(0);
    }
  }

  if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE)) {
    if (!CloseHandle(hFile)) {
      _tprintf(_T("Error: Cannot close the file. Error code: %u \n"), GetLastError());
      _ASSERT(0);
    }
  }

  // Complete

  return 0;
}

bool
CheckDosHeader(PIMAGE_DOS_HEADER pDosHeader) {

  if (pDosHeader == 0) {
    _ASSERT(0);
    return false;
  }

  if (IsBadReadPtr(pDosHeader, sizeof(IMAGE_DOS_HEADER))) {
    return false;
  }

  if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
    return false;
  }

  return true;
}

bool
CheckNtHeaders(PIMAGE_NT_HEADERS pNtHeaders) {

  if (pNtHeaders == 0) {
    _ASSERT(0);
    return false;
  }

  if (IsBadReadPtr(pNtHeaders, sizeof(pNtHeaders->Signature))) {
    return false;
  }

  if (pNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
    return false;
  }

  if (IsBadReadPtr(&pNtHeaders->FileHeader, sizeof(IMAGE_FILE_HEADER))) {
    return false;
  }

  if (IsBadReadPtr(&pNtHeaders->OptionalHeader, pNtHeaders->FileHeader.SizeOfOptionalHeader)) {
    return false;
  }

  bool bPE32Plus = false;

  if (!IsPE32Plus(&pNtHeaders->OptionalHeader, &bPE32Plus)) {
    return false;
  }

  return true;
}

bool
CheckSectionHeaders(PIMAGE_NT_HEADERS pNtHeaders) {
  if (pNtHeaders == 0) {
    _ASSERT(0);
    return false;
  }

  PIMAGE_SECTION_HEADER pSectionHeaders = IMAGE_FIRST_SECTION(pNtHeaders);

  if (IsBadReadPtr(pSectionHeaders,
                   pNtHeaders->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER))) {
    return false;
  }

  return true;
}

bool
CheckDebugDirectory(PIMAGE_DEBUG_DIRECTORY pDebugDir, DWORD DebugDirSize) {
  if ((pDebugDir == 0) || (DebugDirSize == 0)) {
    _ASSERT(0);
    return false;
  }

  if (IsBadReadPtr(pDebugDir, DebugDirSize)) {
    return false;
  }

  if (DebugDirSize < sizeof(IMAGE_DEBUG_DIRECTORY)) {
    return false;
  }

  return true;
}

bool
IsPE32Plus(PIMAGE_OPTIONAL_HEADER pOptionalHeader, bool* bPE32Plus) {
  if (pOptionalHeader->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    *bPE32Plus = false;
  } else if (pOptionalHeader->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
    *bPE32Plus = true;
  } else {
    *bPE32Plus = false;
    return false;
  }

  return true;
}

bool
GetDebugDirectoryRVA(PIMAGE_OPTIONAL_HEADER pOptionalHeader,
                     DWORD* DebugDirRva,
                     DWORD* DebugDirSize) {
  if (pOptionalHeader == 0) {
    _ASSERT(0);
    return false;
  }

  bool bPE32Plus = false;

  if (!IsPE32Plus(pOptionalHeader, &bPE32Plus)) {
    return false;
  }

  if (bPE32Plus) {
    PIMAGE_OPTIONAL_HEADER64 pOptionalHeader64 = (PIMAGE_OPTIONAL_HEADER64)pOptionalHeader;
    *DebugDirRva = pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress;
    *DebugDirSize = pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
  } else {
    PIMAGE_OPTIONAL_HEADER32 pOptionalHeader32 = (PIMAGE_OPTIONAL_HEADER32)pOptionalHeader;
    *DebugDirRva = pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress;
    *DebugDirSize = pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
  }

  if ((DebugDirRva == 0) && (DebugDirSize == 0)) {
    return true;
  } else if ((DebugDirRva == 0) || (DebugDirSize == 0)) {
    return false;
  }
  return true;
}

bool
GetFileOffsetFromRVA(PIMAGE_NT_HEADERS pNtHeaders, DWORD Rva, DWORD* FileOffset) {
  if (pNtHeaders == 0) {
    _ASSERT(0);
    return false;
  }

  bool bFound = false;

  PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeaders);

  for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++, pSectionHeader++) {
    DWORD SectionSize = pSectionHeader->Misc.VirtualSize;

    if (SectionSize == 0)
      pSectionHeader->SizeOfRawData;

    if ((Rva >= pSectionHeader->VirtualAddress) &&
        (Rva < pSectionHeader->VirtualAddress + SectionSize)) {
      bFound = true;
      break;
    }
  }

  if (!bFound) {
    return false;
  }

  INT Diff = (INT)(pSectionHeader->VirtualAddress - pSectionHeader->PointerToRawData);
  *FileOffset = Rva - Diff;

  return true;
}

void
DumpDebugDirectoryEntries(LPBYTE pImageBase, PIMAGE_DEBUG_DIRECTORY pDebugDir, DWORD DebugDirSize) {
  if (!CheckDebugDirectory(pDebugDir, DebugDirSize)) {
    _ASSERT(0);
    return;
  }

  if (pImageBase == 0) {
    _ASSERT(0);
    return;
  }

  int NumEntries = DebugDirSize / sizeof(IMAGE_DEBUG_DIRECTORY);

  if (NumEntries == 0) {
    _ASSERT(0);
    return;
  }

  for (int i = 1; i <= NumEntries; i++, pDebugDir++) {
    DumpDebugDirectoryEntry(pImageBase, pDebugDir);
  }
}

void
DumpDebugDirectoryEntry(LPBYTE pImageBase, PIMAGE_DEBUG_DIRECTORY pDebugDir) {

  if (pDebugDir == 0) {
    _ASSERT(0);
    return;
  }

  if (pImageBase == 0) {
    _ASSERT(0);
    return;
  }

  LPBYTE pDebugInfo = pImageBase + pDebugDir->PointerToRawData;

  if (pDebugDir->Type == IMAGE_DEBUG_TYPE_CODEVIEW) {
    DumpCodeViewDebugInfo(pDebugInfo, pDebugDir->SizeOfData);
  } else if (pDebugDir->Type == IMAGE_DEBUG_TYPE_MISC) {
    DumpMiscDebugInfo(pDebugInfo, pDebugDir->SizeOfData);
  }
}

void
DumpCodeViewDebugInfo(LPBYTE pDebugInfo, DWORD DebugInfoSize) {
  if ((pDebugInfo == 0) || (DebugInfoSize == 0))
    return;

  if (IsBadReadPtr(pDebugInfo, DebugInfoSize))
    return;

  if (DebugInfoSize < sizeof(DWORD))
    return;

  DWORD CvSignature = *(DWORD*)pDebugInfo;

  if (CvSignature == CV_SIGNATURE_NB10) {

    struct CV_INFO_PDB20* pCvInfo = (struct CV_INFO_PDB20*)pDebugInfo;

    if (IsBadReadPtr(pDebugInfo, sizeof(struct CV_INFO_PDB20)))
      return;

    if (IsBadStringPtrA((CHAR*)pCvInfo->PdbFileName, UINT_MAX))
      return;
  } else if (CvSignature == CV_SIGNATURE_RSDS) {
    
    struct CV_INFO_PDB70* pCvInfo = (struct CV_INFO_PDB70*)pDebugInfo;

    if (IsBadReadPtr(pDebugInfo, sizeof(struct CV_INFO_PDB70)))
      return;

    if (IsBadStringPtrA((CHAR*)pCvInfo->PdbFileName, UINT_MAX))
      return;

    char file_name[MAX_FILE_NAME_LENGTH - 4] = {0};
    size_t len_before = strlen(pCvInfo->PdbFileName);
    sprintf(file_name, "%s", PathFindFileNameA(pCvInfo->PdbFileName));
    PathRemoveExtensionA(file_name);
    sprintf(pCvInfo->PdbFileName, ".\\%s.pdb\0", file_name);
    size_t len_after = strlen(pCvInfo->PdbFileName);

    int offset = len_before-len_after;
    int i = 1;
    while (i < offset) {
      pCvInfo->PdbFileName[len_after+i++] = '0';
    }

  } else {

    CHAR* pSig = (CHAR*)&CvSignature;

    printf("CodeView signature: %c%c%c%c \n", pSig[0], pSig[1], pSig[2], pSig[3]);

    if ((pSig[0] == 'N') && (pSig[1] == 'B')) // One of NBxx formats
    {
      struct CV_HEADER* pCvHeader = (struct CV_HEADER*)pDebugInfo;

      _tprintf(_T("CodeView information offset: %08x\n"), pCvHeader->Offset);
    }
  }
}

void
DumpMiscDebugInfo(LPBYTE pDebugInfo, DWORD DebugInfoSize) {
  if ((pDebugInfo == 0) || (DebugInfoSize == 0))
    return;

  if (IsBadReadPtr(pDebugInfo, DebugInfoSize))
    return;

  if (DebugInfoSize < sizeof(IMAGE_DEBUG_MISC))
    return;

  PIMAGE_DEBUG_MISC pMiscInfo = (PIMAGE_DEBUG_MISC)pDebugInfo;

  _tprintf(_T("Data type: %u  Length: %u  Format: %s \n"),
           pMiscInfo->DataType,
           pMiscInfo->Length,
           pMiscInfo->Unicode ? _T("Unicode") : _T("ANSI"));

  if (pMiscInfo->DataType == IMAGE_DEBUG_MISC_EXENAME) {

    if (pMiscInfo->Unicode) {
      if (!IsBadStringPtrW((WCHAR*)pMiscInfo->Data, UINT_MAX))
        wprintf(L"File: %s \n", (WCHAR*)pMiscInfo->Data);
    } else // ANSI
    {
      if (!IsBadStringPtrA((CHAR*)pMiscInfo->Data, UINT_MAX))
        printf("File: %s \n", (CHAR*)pMiscInfo->Data);
    }
  }
}

void
DumpGuid(GUID Guid) {
  _tprintf(_T("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}"),
           Guid.Data1,
           Guid.Data2,
           Guid.Data3,
           Guid.Data4[0],
           Guid.Data4[1],
           Guid.Data4[2],
           Guid.Data4[3],
           Guid.Data4[4],
           Guid.Data4[5],
           Guid.Data4[6],
           Guid.Data4[7]);
}
