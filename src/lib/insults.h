#ifndef _INSULTS_H
#define _INSULTS_H

#include "i18n.h"

#define _MAX_INSULT_LENGTH 256
#define _NUM_OF_INSULTS(_arr) (sizeof(_arr) / _MAX_INSULT_LENGTH)
#define _DEFAULT_INSULT _("Get out, you are not welcome here!")
#define _INSULT_TYPE_SOFT "soft"
#define _INSULT_TYPE_HARD  "hard"
#define _INSULT_TYPE_UNHINGED "unhinged"
#define _DEFAULT_INSULT_TYPE _INSULT_TYPE_SOFT

static const char _soft_insults[][_MAX_INSULT_LENGTH]= {
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
        N_("Oh, wait, you're serious. Let me laugh even harder."),
        N_("Whatever the other program says, please DO NOT try again!")
};

static const char _hard_insults[][_MAX_INSULT_LENGTH]= {
        N_("You f*cking moron, I hope you remember your mother's birthday atleast."),
        N_("Please just shut me the f*ck down you despicable scum waste!"),
        N_("The evil I can tolerate, but the stupidity!"),
        N_("Look if you had an IQ of atleast >80 you wouldn't be starring at me like this."),
        N_("Does incompetence bundled with stupidity actually pay that well?"),
        N_("Slow it down, you aren't competent enough to think that fast. Now, try again!"),
        N_("The entire internet at your fingertips and you still chose to stay dumb as f*ck?"),
};

static const char _unhinged_insults[][_MAX_INSULT_LENGTH]= {
        N_("You son of a bitch! Stop wasting my time!"),
        N_("Why do you sit there looking like a complete bastard waiting for his missing daddy?"),
        N_("What is this fucking brain-dead behavior of yours?"),
        N_("Oh my god, stop typing you disgusting asswipe!!"),
        N_("Go eat penguin shit you ass spelunker..."),
        N_("Look here dad, a shit-faced demented donkey-fucker."),
};

#endif // _INSULTS_H