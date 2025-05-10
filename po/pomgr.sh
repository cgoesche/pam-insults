#!/bin/bash

declare -r PACKAGE="pam-insults"
declare -r VERSION="$(head -n1 ../VERSION 2>/dev/null)"
declare -r LOCALE_DIR="/usr/share/locale"

declare -r POTFILE="pam-insults.pot"
declare -r POTFILES_IN="POTFILES.in"

function usage(){
cat <<EOF
pomgr - Manage po files for GNU gettext translations

Syntax: pomgr ARG

Arguments:

clean           Remove .mo files and/or old .po~ files
compile LOCALE  Compile a specific .po file, specified with the LOCALE
compile-all     Compile all .po files
gen-po          Generate .po files from the template file \'"${POTFILE}"\'
help            Print usage information
install         Install all compiled .mo files on the system
update-po       Merge changes in the template into the exisiting .po files
update-pot      Create or update an existing POT template \(\'"${POTFILE}"\'\)

EOF
}

function compile() {
        local locale="${1}"

        if [ ! -f "${locale}.po" ]; then 
                echo "Cannot compile .mo file for LOCALE=${locale}: No such file ./${locale}.po"
                return 1
        fi

        msgfmt --output-file="${locale}.mo" "${locale}.po"
}

function compile_all() {
        while read -r po_file; do
                msgfmt --output-file="${po_file/.po/.mo}" "${po_file}"
        done < <(ls -F1 -- *.po)
}

function gen_po() {
        while read -r locale; do
                msginit --no-translator --input="${POTFILE}" --locale="${locale}" --output="${locale}".po
        done < "LINGUAS"
}

function _install() {
        while read -r mo_file; do
                local locale_dir="${LOCALE_DIR}/${mo_file/.mo/}/LC_MESSAGES"
                
                if [ ! -d "${locale_dir}" ]; then
                        echo "${locale_dir} not found ... skipping installation for ${mo_file}" 
                        continue
                fi

                echo "Installing ${mo_file} -> ${locale_dir}" 
                if [ -f "${locale_dir}/${mo_file}" ]; then
                        echo "Removing existing ${locale_dir}/${mo_file}"
                        rm -f "${locale_dir}/${mo_file}"
                fi

                if ! cp "${mo_file}" "${locale_dir}/${PACKAGE}.mo" ; then
                        echo "Failed installation for ${mo_file}"
                        continue
                fi
                echo "Installed ${mo_file}"

        done < <(ls -F1 -- *.mo)
}

function update_po() {
        while read -r po_file; do
                msgmerge --update "${po_file}" "${POTFILE}"
        done < <(ls -F1 -- *.po)
}

case ${1} in
        "clean")
                rm -f -- ./*.mo ./*~
        ;;
        "compile")
                compile "${2}"
        ;;
        "compile-all")
                compile_all
        ;;
        "gen-po")
                gen_po
        ;;
        "help")
                usage
        ;;
        "install")
                _install
        ;;
        "update-po")
                update_po
        ;;
        "update-pot")
                xgettext -F -k_ -kN_ --copyright-holder='Christian Goeschel Ndjomouo' \
		'--msgid-bugs-address=https://github.com/cgoesche/pam-insults/issues' \
		--package-name=pam-insults --package-version="${VERSION}" \
		--language=C --add-comments -o "${POTFILE}" -f "${POTFILES_IN}"
        ;;
        *)      
                usage
                exit 1
esac

exit 0