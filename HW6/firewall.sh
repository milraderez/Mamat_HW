#!/bin/bash
chmod +x ./firewall.sh
#read stdin value before loop changes cat + remove tabs.
packets=`cat | tr -d '\t'`
passed_all=""

	while read rule
	do
		#eliminate spaces,empty lines,comment lines, and commas
		rule_cut=`echo "$rule" | sed 's/ //g' |sed 's/,\{2,\}/,/g' |sed '/^$/d'`
		only_rule=`echo "$rule_cut" | grep -o '^[^#]*' | sed 's/^,\{1,\}//'`
		if [[ -n $only_rule ]]; then
			#split the rule to different filters
			readarray -d , -t filter_type <<< "$only_rule"
			passed_1=`echo "$packets" | ./firewall.exe "${filter_type[0]}"`
			passed_2=`echo "${passed_1}" | ./firewall.exe "${filter_type[1]}"`
			passed_3=`echo "${passed_2}" | ./firewall.exe "${filter_type[2]}"`
			passed_4=`echo "${passed_3}" | ./firewall.exe "${filter_type[3]}"`
			#insert \n after each passed packet to ensure proper printing
			passed_all+=`echo "${passed_4}" |sed 's/src-ip/\nsrc-ip/'`
		fi
	done < "$1"
# -e to treat the \n, sed for removing emtpy lines and spaces, and sort
echo -e "$passed_all" | sed '/^$/d' | sed 's/ //g' | sort


