if echo "$1" | grep -Eq 'i[[:digit:]]'; then
  echo i386
else
  echo "$1" | grep -Eo '^[[:alnum;]_]*'
fi

