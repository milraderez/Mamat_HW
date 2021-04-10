wget https://premierleague.com/players
cat players | grep -P -o "/players/[0-9]+/[a-z A-Z -]+/overview" players >> mid
rm players
sed -i 's/\/players/https:\/\/www.\premierleague\.com\/players/' mid
awk 'BEGIN{FS=OFS=", "}{$2 ="Midfielder, "}1' mid >> temp_results.csv
while read -r line; do wget -O- $line | grep -P -i -c 'Midfielder' >> temp_count.csv;done <mid
awk 'FNR==NR{a[NR] = $1;next}{$3 = a[FNR]}1' temp_count.csv temp_results.csv >> temp_results.csv
rm temp_count.csv
echo "Total Players: $(cat mid |wc -l) " > results.csv
rm mid
cat temp_results.csv | grep -P -o "https://www.premierleague.com/players/[0-9]+/[a-z A-Z -]+/overview, Midfielder, [1-9]+" temp_results.csv >> results.csv
rm temp_results.csv