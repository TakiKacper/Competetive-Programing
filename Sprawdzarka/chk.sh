g++ -std=c++17 -O2 "$1" -o a.out || exit 1
split() { awk -v RS="" '{$1=$1; print}' "$1"; }
mapfile -t in < <(split "$2")
mapfile -t out < <(split "$3")

for i in "${!in[@]}"; do
    r=$(echo "${in[i]}" | ./a.out | tr '\n' ' ' | awk '{$1=$1; print}')
    if [[ $r == "${out[i]}" ]]; then echo "$((i+1)): OK"
    else echo "$((i+1)): Not OK"; echo "Exp: ${out[i]}"; echo "Got: $r"; echo ""; fi
done

rm -f a.out
