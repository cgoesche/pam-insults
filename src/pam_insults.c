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
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <security/pam_modules.h>

#include "lib/i18n.h"

#define _INSULT_MAX_LENGTH 128
#define _NUM_OF_INSULTS(x) (sizeof(x) / _INSULT_MAX_LENGTH)
#define _DEFAULT_INSULT _("Get out, you are not welcome here!")

static const char _insults[][_INSULT_MAX_LENGTH]= {
        N_("Stop the idiotic arguing already."),
        N_("Get out, you are not welcome here!"),
        N_("Maybe if you used more than just two fingers..."),
        N_("Listen, broccoli brains, I don't have time to listen to this trash."),
        N_("I'd like to know what drugs you take?"),
        N_("Take a stress pill and think things over."),
        N_("What, what, what, what, what, what, what, what, what, what?"),
        N_("iPhone unavailable, try again in 24 hours."),
        N_("It can only be attributed to human error."),
        N_("BOB says:  You seem to have forgotten your passwd, enter another!"),
        N_("You speak an infinite deal of nothing."),
        N_("Have you considered trying to match wits with a rutabaga?"),
        N_("We don't break user space!"),
        N_("I'd challenge you to a battle of wits, but I see you are unarmed."),
        N_("I see you're playing stupid again. And you're winning."),
        N_("I'm reporting you ... and it's not for what you think."),
        N_("Look who forgot his password, again."),
        N_("AGI is not even necessary at this point, a few GPUs will do the job."),
        N_("PAM: Account locked for 3 years."),
        N_("Some cause happiness wherever they go; others whenever they go."),
        N_("Why do you sit there looking like an envelope without any address on it?"),
        N_("You wasted valuable CPU time with this non-sense."),
        N_("Time to use a password manager, dummy."),
        N_("Eww, what a nasty password. Access denied!"),
        N_("You do that again and see what happens..."),
        N_("Pathetic!")
};

static void 
insult()
{
        size_t size; 
        size_t i;
        char *ins;

        srand(time(NULL));

        // Enable localization of insults via gettext
        bindtextdomain(_DOMAINNAME, _LOCALEDIR);
        textdomain(_DOMAINNAME);

        size = _NUM_OF_INSULTS(_insults);
        i = rand() % size;
        ins = (char *)malloc(_INSULT_MAX_LENGTH);

        if (i >= 0 && i < size) {
                strcpy(ins, _(_insults[i]));
        } else {
                strcpy(ins, _DEFAULT_INSULT); 
        }
        fprintf(stderr, "%s\n", ins);
        free(ins);
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
