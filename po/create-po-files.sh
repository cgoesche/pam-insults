#!/bin/bash

while read -r locale; do
  msginit --no-translator --input=pam-insults.pot --locale="${locale}" --output="${locale}".po
done < "LINGUAS"