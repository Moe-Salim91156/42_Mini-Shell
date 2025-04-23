#!/bin/bash

# Path to your minishell executable
MINISHELL="./minishell"

# Temp file to feed commands into minishell
TMP_INPUT="tmp_input.txt"

# List of test cases with expected error keyword

declare -a tests=(
  "| ls:|"
  "ls |:newline"
  "cat << EOF << EOF <<:<<"
  "cat << EOF <:newline"
  "ls |       | asdf:|"
  "<>:<"
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

