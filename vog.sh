#!/bin/sh
# Envoie un module vers son repo Vogsphere.
# Usage : ./vog.sh Module-00 <url-vogsphere>
# Seuls les fichiers suivis par git partent (pas de .o ni de binaires),
# sans les PDF ni les .gitkeep.
set -e

MOD="$1"
URL="$2"

if [ -z "$MOD" ] || [ -z "$URL" ]; then
	echo "Usage : ./vog.sh Module-0X <url-vogsphere>"
	exit 1
fi
cd "$(dirname "$0")"
if [ ! -d "$MOD" ]; then
	echo "Dossier $MOD introuvable"
	exit 1
fi
if ! git diff --quiet HEAD -- "$MOD"; then
	echo "Des modifs non commitées dans $MOD : commit-les d'abord."
	exit 1
fi

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

git clone -q "$URL" "$TMP/vog"
# Vide le repo Vogsphere (sauf .git) puis copie la version commitée du module
find "$TMP/vog" -mindepth 1 -maxdepth 1 ! -name .git -exec rm -rf {} +
git archive HEAD "$MOD" | tar -x -C "$TMP"
cp -R "$TMP/$MOD"/. "$TMP/vog"/
find "$TMP/vog" \( -name '*.pdf' -o -name '.gitkeep' \) -not -path '*/.git/*' -delete

cd "$TMP/vog"
git add -A
if git diff --cached --quiet; then
	echo "Rien de nouveau à envoyer."
	exit 0
fi
echo "Fichiers envoyés :"
git diff --cached --name-status
printf "Pousser vers la Vogsphere ? [o/N] "
read -r ok
[ "$ok" = "o" ] || { echo "Annulé."; exit 0; }
git commit -qm "$MOD"
git push -q
echo "Envoyé."
