#!/bin/bash
chmod +x ./scrape_players.sh
wget https://premierleague.com/players
#taking only the relevant players
#rel = relevant players 
cat players | grep -P -o "/players/[0-9]+/[a-z A-Z -]+/overview" players >> rel
rm players
sed -i 's/\/players/https:\/\/www.\premierleague\.com\/players/' rel
#adding the word midfielder, spaces and commas to the file
#tres.csv = temp_results.csv
awk 'BEGIN{FS=OFS=", "}{$2 ="Midfielder, "}1' rel >> tres.csv
#counting the number of "midfielder" appearences for each player
#tco.csv = temp_count.csv
while read -r line;
do wget -O- $line | grep -P -i -c 'Midfielder' >> tco.csv;done < rel   
#adding the numbers from temp count in line
awk 'FNR==NR{a[NR] = $1;next}{$3 = a[FNR]}1' tco.csv tres.csv >> tres.csv
rm tco.csv
echo "Total Players: $(cat rel |wc -l) " > Results.csv
rm rel
#picking only the "real" midfielders for the final file
address="https://www.premierleague.com/players"
look_for="[0-9]+/[a-z A-Z -]+/overview, Midfielder, [1-9]+"
cat tres.csv |
 grep -P -o "$address/$look_for" tres.csv >> Results.csv
rm tres.csv