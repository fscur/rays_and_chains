declare -a recomended_extensions=(
    "ms-vscode.cpptools"
    "wayou.vscode-todo-highlight"
    "xaver.clang-format"
    "robertohuertasm.vscode-icons")

for i in "${recomended_extensions[@]}"
do
    code --install-extension $i
done

code --add $(pwd)