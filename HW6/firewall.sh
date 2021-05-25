#!/bin/bash
chmod +x ./firewall.sh
#to read stdin value before loop changes cat.
packets=`cat`
passed_all=""

	while read rule
	do
		#eliminate spaces,empty lines, and comment lines
		rule_cut=`echo "$rule" | sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
		if [[ -n $rule_cut ]]; then
			#split the rule to different filters
			readarray -d , -t filter_type <<< "$rule_cut"
			passed_1=`echo "$packets" | ./firewall.exe "${filter_type[0]}"`
			passed_2=`echo "${passed_1}" | ./firewall.exe "${filter_type[1]}"`
			passed_3=`echo "${passed_2}" | ./firewall.exe "${filter_type[2]}"`
			passed_4=`echo "${passed_3}" | ./firewall.exe "${filter_type[3]}"`
			#insert \n after each passed packet to ensure proper printing
			passed_all+=`echo "${passed_4}" |sed 's/src-ip/\nsrc-ip/'`
		fi
	done < "$1"
#-e to treat the \n, sed for removing emtpy lines and spaces, and sort + unique
echo -e "$passed_all" | sed '/^$/d' | sed 's/ //g' | sort -u


