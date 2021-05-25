#!/bin/bash
chmod +x ./firewall.sh
packets=`cat`
passed_all=""

	while read rule
	do
		rule_cut=`echo "$rule" | sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
		if [[ -n $rule_cut ]]; then
			readarray -d , -t filter_type <<< "$rule_cut"
			passed_1=`echo "$packets" | ./firewall.exe "${filter_type[0]}"`
			passed_2=`echo "${passed_1}" | ./firewall.exe "${filter_type[1]}"`
			passed_3=`echo "${passed_2}" | ./firewall.exe "${filter_type[2]}"`
			passed_4=`echo "${passed_3}" | ./firewall.exe "${filter_type[3]}"`
			passed_all+=`echo "${passed_4}" |sed 's/src-ip/\nsrc-ip/'`
		fi
	done < "$1"
	
echo -e "$passed_all" | sed '/^$/d' | sed 's/ //g' | sort -u


