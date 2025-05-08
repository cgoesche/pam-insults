# pam-insults

**pam-insults** (**pam_insults**) is a PAM module that will print an insult to stderr(3) whenever a user enters a bad password before
returning a failure code to the calling application through the PAM framework.

> :note:
> 
> This module was primarily created for academic purposes, to get a better understanding of the PAM framework and its internals, but can still reliably deny access in failed authentication attempts just like the standard pam_deny module.

## Installation

Packaging efforts are ongoing and once uploaded to the major OS archives this section will be updated with instructions.

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

> :note:
> 
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

## Feedback

I highly appreciate and welcome all types of feedback and bug reports either via the issue section in this repo or via email cgoesc2@wgu.edu.