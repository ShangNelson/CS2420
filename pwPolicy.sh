#!/bin/sh

echo -n "PASS_MAX_DAYS: "
read MAX

if [ "$MAX" = '' ];
then
	echo "Set to Default: 60"
	MAX=60
fi


echo -n "PASS_MIN_DAYS: "
read MIN

if [ "$MIN" = '' ];
then
        echo "Set to Default: 1"
        MIN=1
fi


echo -n "PASS_WARN_AGE: "
read AGE

if [ "$AGE" = '' ];
then
        echo "Set to Default: 7"
        AGE=7
fi


echo''
for i in "PASS_MAX_DAYS",$MAX,"Max Days" "PASS_MIN_DAYS",$MIN,"Min Days" "PASS_WARN_AGE",$AGE,"Warn Age"
do
	IFS=","
	set -- $i

	LINES=$(grep $1 /etc/login.defs | grep -v "#")
	EXPR='/'$LINES'/ c\\'$1'   '$2
	sed -i "$EXPR" /etc/login.defs
	echo "Changed $3"
done

echo''
echo''

echo -n "Password Retry Limit (retry): "
read RETRY

if [ "$RETRY" = '' ];
then
        echo "Set to Default: 4"
        RETRY=4
fi


echo -n "Password Minlength (minlen): "
read MINLEN

if [ "$MINLEN" = '' ];
then
        echo "Set to Default: 8"
        MINLEN=8
fi


echo -n "Password Max Repeat (maxrepeat): "
read MAXREP

if [ "$MAXREP" = '' ];
then
        echo "Set to Default: 3"
        MAXREP=3
fi


echo -n "Password Uppercase (ucredit): "
read UPPER

if [ "$UPPER" = '' ];
then
        echo "Set to Default: True"
        UPPER=1
fi


echo -n "Password Lowercase (lcredit): "
read LOWER

if [ "$LOWER" = '' ];
then
        echo "Set to Default: True"
        LOWER=1
fi


echo -n "Password Numerics (dcredit): "
read NUMERICS

if [ "$NUMERICS" = '' ];
then
        echo "Set to Default: True"
        NUMERICS=1
fi


echo -n "Password Specials (ocredit): "
read SPECIALS

if [ "$SPECIALS" = '' ];
then
        echo "Set to Default: True"
       	SPECIALS=1
fi


echo -n "Password Min Changes (difok): "
read MINCHANGES

if [ "$MINCHAGES" = '' ];
then
        echo "Set to Default: 4"
        MINCHANGES=4
fi

echo -n "Check password against past passwords?: "
read REMEMBER

if [ "$REMEMBER" = '' ];
then
		echo "Set to Default: 3"
		REMEMBER=3
fi

echo -n "Check password against cracklib?: "
read CRACKLIB

if [ "$CRACKLIB" = '' ];
then
		echo "Set to Default: 1"
		CRACKLIB=1
fi

echo -n "Enforcing password?: "
read ENFORCING

if [ "$ENFORCING" = '' ];
then
		echo "Set to Default: 1"
		ENFORCING=1
fi


echo ''

for i in "retry",$RETRY,"Retry Limit" "minlen",$MINLEN,"Minimum Length" "maxrepeat",$MAXREP,"Maximum Repeats" "ucredit",$UPPER,"Uppercase" "lcredit",$LOWER,"Lowercase" "dcredit",$NUMERICS,"Numerics" "ocredit",$SPECIALS,"Specials" "difok",$MINCHANGES,"Minimum Changes" "remember",$REMEMBER,"Remembering" "enforcing",$ENFORCING,"Enforcement" "dictcheck",$CRACKLIB,"Checking against library"
do
	IFS=","
	set -- $i

	if grep -oq "$1.*" /etc/pam.d/common-password;
	then
	        FIND=$(grep -o "$1.*" /etc/pam.d/common-password)
	        sed -i 's/'$FIND'*/'$1'='$2'/' /etc/pam.d/common-password
	        echo "Changed Password "$3
	elif !(grep -oq "$1.*" /etc/pam.d/common-password);
	then
	        sed -i '/unix.so/s/$/ '$1'='$2'/' /etc/pam.d/common-password
	        echo "Changed Password "$3
	fi
done

echo "Don't forget to change weak passwords <3"
