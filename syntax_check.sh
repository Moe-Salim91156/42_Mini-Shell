#!/bin/bash

# Path to your minishell executable
MINISHELL="./minishell"

# Temp file to feed commands into minishell
TMP_INPUT="tmp_input.txt"

# List of test cases with expected error keyword
declare -a valid_tests=(
  "'c'lear"
  "'e'cho"
  "\"e\"cho"
  "ls"
  "                                         ls''                                "
  "ls'' "
  "ls"" "
  "echo hello"
  "cat << EOF\nhello\nEOF"
  "ls | grep txt"
  "cat file.txt | sort > sorted.txt"
  "echo hi > file && cat < file"
  "cat << EOF | grep hi\nhi\nEOF"
)

echo -e "\n✅ Running minishell valid syntax tests:\n"

j=1
for valid_input in "${valid_tests[@]}"; do
  # If input contains newlines, use printf to preserve them
  output=$(printf "%b\n" "$valid_input" | $MINISHELL 2>&1)
  
  # Expecting no syntax error
  if echo "$output" | grep -qi "syntax error"; then
    echo "❌ Valid Test $j Failed: '$valid_input'"
    echo "   ➤ Unexpected syntax error in output:"
    echo "$output"
  else
    echo "✅ Valid Test $j Passed: '$valid_input'"
  fi
  ((j++))
done

declare -a tests=(
  "| ls:syntax error"
  "ls \"\":No such file or directory"
  "ls '':No such file or directory"
  "ls \"\"\"\":No such file or directory"
  "ls |:syntax error"
  "cat << EOF << EOF <<:<<"
  "cat << EOF <:newline"
  "ls |       | asdf:|"
  "<>:<"
  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>:syntax error"
  "ls || ls:|"
  "ls |||| cat:|"
  "|:|"
  "> file >:newline"
  "ls > > file:>"
  ">> >> file:>"
  "< < file:<"
  "cat << <<:<<"
  "cat | | grep:|"
  "cat ||||| grep:|"
  "cat <<:<<"
)
echo -e "\n🧪 Running minishell syntax error tests:\n"

i=1
for test_case in "${tests[@]}"; do
  IFS=':' read -r input expected <<< "$test_case"

  echo "$input" > "$TMP_INPUT"

  output=$(echo "$input" | $MINISHELL 2>&1)

  if echo "$output" | grep -q "$expected"; then
    echo "✅ Test $i Passed: '$input'"
  else
    echo "❌ Test $i Failed: '$input'"
    echo "$expected"
    echo "   ➤ Expected to find: '$expected'"
    echo "   ➤ Output was: $output"
  fi
  ((i++))
done

rm -f "$TMP_INPUT"

