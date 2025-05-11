# pam-insults

**pam-insults** is a PAM module that will print an insult to stderr(3) whenever a user enters a bad password before
returning a failure code to the calling application through the PAM framework.

> This module was primarily created for academic purposes, to get a better understanding of the PAM framework and its internals, but can still reliably deny access in failed authentication attempts just like the standard pam_deny module. Nevertheless, as of now I do not recommend installing the module in a highly critical production environment since it requires more battle testing and peer reviews.

## Installation

Packaging efforts for major distributions are planned for the future once the module is stable enough.

## Building

Building the module is fairly simple and straightforward. Simply follow the steps below and make sure you have the needed build-/runtime dependencies installed. 

### Dependencies

#### Debian/Ubuntu

```
sudo apt install git build-essential libpam0g-dev libpam-runtime asciidoctor manpages
```

#### RHEL/Fedora/CentOS

```
sudo dnf install git make gcc pam pam-devel asciidoctor man-pages
```

### Clone

```
git clone https://github.com/cgoesche/pam-insults.git
cd pam-insults
```

### Build

```
make
make install
```

This will install the **pam_insults.so** module in your systems PAM module directory and a manpage `pam_insults(8)` along with it in `/usr/share/man/man8`.

> If you get an error message similar to `cp: cannot create regular file '/usr/lib/security/.': No such file or directory` then your system has the PAM modules installed in an unusual location. See below on how to find the PAM modules directory and fix this error.

### Finding the PAM module directory

If you have PAM installed on your system (most likely the case) you can search for its module directory with the command below:

```
sudo find / -type f -iname pam_unix.so 2>/dev/null | grep -E '^/usr/.*/security/pam_unix.so$'
```

This should return an absolute path to a directory that contains the PAM modules. You can use that directory now to install **pam_insults.so** like so:

```
export PAM_MODULES_DIR="<directory>"
make install
```

## Configuration

Now, where you have the module installed you need to modify the relevant PAM  configuration(s) in `/etc/pam.d/`. The most common configuration types will be shown in this example, but for the rest you'd have to consult your distributions manual to find the default PAM configuration files.

### Debian/Ubuntu

For Debian and Ubuntu the configuration files you want to look at are `common-auth`, `common-password` and `common-account`.

In all these files simply replace the line containing `pam_deny.so` with the one below:

```
<type>    requisite    pam_insults.so
```

Where `<type>` can stay the same and is essentially what you can infer from the respective file name.

### RHEL/Fedora/CentOS

For Red-hat based systems there is mostly one file that provides a system wide PAM configuration baseline, namely `system-auth`.

Here you can do the same as in the previous section with the difference that you do everything in the same file.

### Options

The module accepts the following two option arguments:

`quiet` - Turns off the printing of insults.

`type=` - Sets the type of insults to print. Recognized values for type are `soft`, `hard` and `unhinged`. The default is `soft` when no or an unknown type is specified.

## Testing

If you have successfully followed all steps until here you are ready to test the insults. Simply run any command in the terminal that requires some sort of PAM authentication like `sudo su`, `passwd` or `su -`.

### Example

```
$ sudo su
[sudo] password for <username>: 
I see you're playing stupid again. And you're winning.
Sorry, try again.
[sudo] password for <username>: 
Get out, you are not welcome here!
Sorry, try again.
[sudo] password for <username>: 
Eww, what a nasty password. Access denied!
sudo: 3 incorrect password attempts
```

## Localization

If you wish to have insults in different languages you can translate the default English version with the help of the auto-generated template files in `po/`.
The localization has been implemented using GNU gettext and relies on binary GNU MO files (.mo). Below are instructions on how to compile these binaries and install them 
on your system with the help of the `po/pomgr.sh` script.

### Preparation

Clean up all temporary files or previously generated MO files.

```
cd po/
./pomgr.sh clean
```

### Translation

Locate your preferred locales `.po` file and open it with your favorite text editor or with a specialized tool like Poedit.
For example, if you want to translate for the `German, Germany` locale, you would need to edit `po/de.po`.

In the file itself you will find an initial comment section, header fields and the actual messages (insults) that you want to translate.
You can edit the header fields if you wish but it is not necessary for this use case. What you want to focus on are the `msgstr` lines.

Simply put your translation in quotes below the respective `msgid` and proceed until you are done.

An example for the German language:

```
#: ../src/lib/insults.h:41
msgid "Whatever the other program says, please DO NOT try again!"
msgstr "Was auch immer das andere Programm sagt, versuch es bitte NICHT erneut!"
```

More information on how to translate `.po` files can be found here: [Translation Project](https://translationproject.org/html/translators.html).

### Compilation

Once you have finished your translation it is time to compile the `.po` files to `.mo`, as shown below.

```
./pomgr.sh compile <LOCALE>
```

Replace `<LOCALE>` with your languages locale abbreviation which can be derived from the file name itself, e.g. for `German, Germany = de`, 
`French, France = fr`, and so on.

Optionally, you can also run `./pomgr.sh compile-all` which will compile MO files for all locales present in `po/`.

### Installation

Finally, you can install your compiled MO files into your system with this command:

```
sudo ./pomgr.sh install
```

The script will intelligently determine the right directory for each MO file and change its final name to `pam-insults.mo` in the respective directories in
`/usr/share/locale/<LOCALE>/LC_MESSAGES/`.

### Testing

To test the translation, you can either change the systems language in your desktop environments settings or by exporting `LC_MESSAGES` with the 
appropriate locale value.

An example for the `German, Germany` locale:

```
$ export LC_MESSAGES="de_DE.UTF-8"
$ passwd
Geben Sie das aktuelle Passwort ein:
Raus hier, du bist hier nicht willkommen!
passwd: Fehler beim Ändern des Authentifizierungstoken
passwd: password unchanged
```

## Feedback

I highly appreciate and welcome all types of feedback and bug reports either via the issue section in this repo or via email cgoesc2@wgu.edu.
