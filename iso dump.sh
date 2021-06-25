SORT="sort"
hexdump="hexdump"
type="e"
output="iso.txt"
input="Slidoor.iso"

set -x

$hexdump "$input" | \
    grep -P '^[0-9a-f]+\s' | \
    grep -v '^0000000000000000' | \
    grep -vP '^[0-9a-f]+\s.....d' | \
    grep -vP '\*ABS\*' |
    sed -E 's/^([0-9a-f]+)\s.{7}\s\S+\s+\S+\s+(.hidden )?(.*)/\1 \3/' | \
    $SORT > "$output"
