# Vérifie : ligne 1 = entrée, ligne 2 = entrée triée, puis 2 lignes de temps
out="$(cat)"; input="$*"
before="$(echo "$out" | sed -n 1p | grep -oE '[0-9]+' | tr '\n' ' ' | sed 's/ $//')"
after="$(echo "$out" | sed -n 2p | grep -oE '[0-9]+' | tr '\n' ' ' | sed 's/ $//')"
sorted="$(printf '%s\n' $input | sort -n | tr '\n' ' ' | sed 's/ $//')"
[ "$before" = "$input" ] || { echo "ligne 1 : la suite d'entrée non triée est attendue"; exit 1; }
[ "$after" = "$sorted" ] || { echo "ligne 2 : la suite n'est pas correctement triée (doublons compris)"; exit 1; }
[ "$(echo "$out" | wc -l)" -ge 4 ] || { echo "4 lignes attendues : avant, après, et le temps pour chaque conteneur"; exit 1; }
