#!/bin/bash

function gen_po() {
        while read -r locale; do
                msginit --no-translator --input=pam-insults.pot --locale="${locale}" --output="${locale}".po
        done < "LINGUAS"
}

function compile_po() {
        while read -r pofile; do
                msgfmt --output-file="${pofile/.po/.mo}" "${pofile}"
        done < <(ls -F1 -- *.po)
}

case ${1} in
        "gen-po")
                gen_po
        ;;
        "compile")
                compile_po
        ;;
        *)      
                update_pot
esac