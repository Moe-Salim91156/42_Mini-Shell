#!/bin/bash

# Path to your minishell executable
MINISHELL="./minishell"

# Temp file to feed commands into minishell
TMP_INPUT="tmp_input.txt"

# List of test cases with expected error keyword
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
  "ls"" "
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
"echo >file"         # This is legal
"echo hi >file && echo ok"
"echo > file"
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

echo -e "\n✅ Running minishell valid syntax tests number 2:\n"
j=1
for valid_input in "${valid_tests2[@]}"; do
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
declare -a invalid_test_2=(
"| ls"                      # starts with pipe
"ls |"                      # ends with pipe
"|| ls"                     # double pipe
"ls ||"                     # trailing ||
"ls |||| cat"               # madness
"> file >"                  # redirection into nothing
">>"                        # redirection into nothing
"< < file"                  # double input redirection with no command
"> file <"                  # incomplete sequence
"cat << <<"                 # malformed heredoc
"cat <<< file"              # <<< unsupported operator
">>>>>>>>>>>>"
"cat < | > out.txt"         # malformed input and output mix
"cat | | grep"              # double pipe
"cat << EOF << EOF <<EOF"   # chained heredoc without commands
"echo > > > file"           # nested redirection with no target
"<<<file"                   # unsupported operator
"<<<<EOF\ntext\nEOF"        # multiple heredocs without command
"cat <<EOF\nhello\nEOF extra" # extra token after heredoc
">"                         # lone operator
"<"                         # lone operator
"<<"                        # lone heredoc
"|"                         # lone pipe
"ls > > file"               # redirect to redirect
"> | ls"                    # output to pipe
"< >"                       # mixed bad redirections
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

echo -e "\n🧪 Running minishell syntax error tests->2:\n"
i=1
for test_case in "${invalid_test_2[@]}"; do
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

