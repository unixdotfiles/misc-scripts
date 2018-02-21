T='gYwQ'
printf "\n                40m     41m     42m     43m     44m     45m     46m     47m\n";
for FGs in '    m' '   1m' '  30m' '1;30m' '  31m' '1;31m' '  32m' '1;32m' \
        '  33m' '1;33m' '  34m' '1;34m' '  35m' '1;35m' '  36m' '1;36m' \
  '  37m' '1;37m'; do
  FG="${FGs// /}"
  printf " $FGs \033[$FG  $T  "
  for BG in 40m 41m 42m 43m 44m 45m 46m 47m; do
    printf "\033[$FG\033[$BG  $T \033[0m\033[$BG \033[0m";
  done
printf "\n"
done
printf "\n   +  "
for i in {0..35}; do
  printf "%2b " $i
done
printf "\n\n %3b  " 0
for i in {0..15}; do
  printf "\033[48;5;${i}m  \033[m "
done
#for i in 16 52 88 124 160 196 232; do
for i in {0..6}; do
  i=$(( i * 36 + 16 ))
  printf "\n\n %3b  " $i
  for j in {0..35}; do
    val=$(( i + j ))
    printf "\033[48;5;${val}m  \033[m "
  done
done
printf "\n"
