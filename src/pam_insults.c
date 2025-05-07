/*
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
#include <security/pam_ext.h>

#define INSULTS_LIST_LEN 24

char insults[INSULTS_LIST_LEN][256] = { 
        "Stop the idiotic arguing already.",
        "Get out!",
        "Maybe if you used more than just two fingers...",
        "Listen, broccoli brains, I don't have time to listen to this trash.",
        "I'd like to know what drugs you take?",
        "Take a stress pill and think things over.",
        "What, what, what, what, what, what, what, what, what, what?",
        "This is how the world should work, but in the real world it is just BS.",
        "It can only be attributed to human error.",
        "BOB says:  You seem to have forgotten your passwd, enter another!",
        "You speak an infinite deal of nothing.",
        "Have you considered trying to match wits with a rutabaga?",
        "We don't break user space!",
        "I'd challenge you to a battle of wits, but I see you are unarmed.",
        "I see you're playing stupid again. And you're winning.",
        "I'm reporting you ... for your retardedness.",
        "Ohh look who forgot his password, again.",
        "You are one of the reasons why AI is replacing humans (not me).",
        "PAM: Account locked for 3 years.",
        "Some cause happiness wherever they go; others whenever they go.",
        "Why do you sit there looking like an envelope without any address on it?",
        "You wasted valuable CPU time with this non-sense",
        "Time to use a password manager dummy.",
        "PAM: Access denied, I just don't like you."
};

static void insult()
{       
        int n; 
        srand(time(NULL));

        n = rand() % INSULTS_LIST_LEN;

        fprintf(stderr, "%s\n", insults[n]);
}

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
