#!/bin/bash

# Path to your minishell executable
MINISHELL="./minishell"

# List of valid test cases (should NOT trigger syntax errors)
declare -a valid_tests=(
  "<o1 cat > out | <o1 cat"
  "<o1 cat > out|<o1 cat|<o1 << EOF cat"
  "<o1 cat|<o1 cat <o1|ls >o2"
  "'c'lear"
  "'e'cho"
  "\"e\"cho"
  "ls"
  "                                         ls''                                "
  "ls'' "
  "ls\"\" "
  "echo hello"
  "cat << EOF\nhello\nEOF"
  "ls | grep txt"
  "cat file.txt | sort > sorted.txt"
  "echo hi > file && cat < file"
  "cat << EOF | grep hi\nhi\nEOF"
)

declare -a valid_tests2=(
  "echo hello"
  "ls | wc"
  "cat < input.txt > output.txt"
  "cat <<EOF\nhello\nEOF"
  "cat <<EOF | grep hi\nhi\nEOF"
  "echo '>'"
  "echo 'some text' > file.txt"
  "ls | grep txt | sort"
  "echo \"hello\""
  "echo \"'nested quotes'\""
  "echo '\"nested quotes\"'"
  "ls >out && cat <in"
  "cat<<EOF\nmulti\nline\nEOF"
  "cat <<EOF\n>\nEOF"
  "cat <<EOF\n|\nEOF"
  "echo ''"
  "echo \"\""
  "ls''"
  "ls\"\""
  "echo >file"
  "echo hi >file && echo ok"
  "echo > file"
)

echo -e "\n✅ Running minishell valid syntax tests:\n"
j=1
for valid_input in "${valid_tests[@]}"; do
  output=$(printf "%b\n" "$valid_input" | $MINISHELL 2>&1)
  
  if echo "$output" | grep -qi "syntax error"; then
    echo "❌ Valid Test $j Failed: '$valid_input'"
    echo "   ➤ Unexpected syntax error:"
    echo "$output"
  else
    echo "✅ Valid Test $j Passed: '$valid_input'"
  fi
  ((j++))
done

echo -e "\n✅ Running minishell valid syntax tests (Set 2):\n"
j=1
for valid_input in "${valid_tests2[@]}"; do
  output=$(printf "%b\n" "$valid_input" | $MINISHELL 2>&1)
  
  if echo "$output" | grep -qi "syntax error"; then
    echo "❌ Valid Test 2.$j Failed: '$valid_input'"
    echo "   ➤ Unexpected syntax error:"
    echo "$output"
  else
    echo "✅ Valid Test 2.$j Passed: '$valid_input'"
  fi
  ((j++))
done

# Syntax error tests with expected substring to match
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

echo -e "\n🧪 Running minishell syntax error tests (with expected keywords):\n"
i=1
for test_case in "${tests[@]}"; do
  IFS=':' read -r input expected <<< "$test_case"
  output=$(echo "$input" | $MINISHELL 2>&1)

  if echo "$output" | grep -q "$expected"; then
    echo "✅ Error Test $i Passed: '$input'"
  else
    echo "❌ Error Test $i Failed: '$input'"
    echo "   ➤ Expected: '$expected'"
    echo "   ➤ Got: $output"
  fi
  ((i++))
done

# Tests that should *just* fail with any syntax error
declare -a invalid_test_2=(
  "| ls"
  "ls |"
  "|| ls"
  "ls ||"
  "ls |||| cat"
  "> file >"
  ">>"
  "< < file"
  "> file <"
  "cat << <<"
  "cat <<< file"
  ">>>>>>>>>>>>"
  "cat < | > out.txt"
  "cat | | grep"
  "echo > > > file"
  "<<<file"
  ">"
  "<"
  "<<"
  "|"
  "ls > > file"
  "> | ls"
  "< >"
)

echo -e "\n🧪 Running minishell syntax error tests (generic errors):\n"
i=1
for input in "${invalid_test_2[@]}"; do
  output=$(printf "%b\n" "$input" | $MINISHELL 2>&1)

  if echo "$output" | grep -qi "syntax error"; then
    echo "✅ Generic Error Test $i Passed: '$input'"
  else
    echo "❌ Generic Error Test $i Failed: '$input'"
    echo "   ➤ Expected generic syntax error."
    echo "   ➤ Got: $output"
  fi
  ((i++))
done

