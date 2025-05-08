/*
pam_insults module

Copyright © 2025 Christian Goeschel Ndjomouo <cgoesc2@wgu.edu>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <security/pam_modules.h>

#include "insults.h"

static void 
insult()
{
        srand(time(NULL));
        size_t size = NUM_OF_INSULTS(insults);
        size_t i = rand() % size;

        if (i >= 0 && i < size) {
                fprintf(stderr, "%s\n", insults[i]);
        } else {
                fprintf(stderr, "Get out, you are not welcome here!\n"); 
        }
}

// PAM function definitions
//
// authentication management functions
int 
pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult();
        return PAM_AUTH_ERR;
}

int 
pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult();
        return PAM_CRED_ERR;
}

// account management function
int 
pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult();
        return PAM_AUTH_ERR;
}

// password management function
int 
pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult();
        return PAM_AUTHTOK_ERR;
}

// session management functions
int
pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return PAM_IGNORE;
}

int
pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return PAM_IGNORE;
}
