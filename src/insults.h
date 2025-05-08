#ifndef INSULTS_H
#define INSULTS_H

#define _INSULT_MAX_LENGTH 128
#define _NUM_OF_INSULTS(x) (sizeof(x) / _INSULT_MAX_LENGTH)
#define _DEFAULT_INSULT "Get out, you are not welcome here!"

static const char _insults[][_INSULT_MAX_LENGTH]= {
        "Stop the idiotic arguing already.",
        "Get out, you are not welcome here!",
        "Maybe if you used more than just two fingers...",
        "Listen, broccoli brains, I don't have time to listen to this trash.",
        "I'd like to know what drugs you take?",
        "Take a stress pill and think things over.",
        "What, what, what, what, what, what, what, what, what, what?",
        "iPhone unavailable, try again in 24 hours.",
        "It can only be attributed to human error.",
        "BOB says:  You seem to have forgotten your passwd, enter another!",
        "You speak an infinite deal of nothing.",
        "Have you considered trying to match wits with a rutabaga?",
        "We don't break user space!",
        "I'd challenge you to a battle of wits, but I see you are unarmed.",
        "I see you're playing stupid again. And you're winning.",
        "I'm reporting you ... and it's not for what you think.",
        "Look who forgot his password, again.",
        "AGI is not even necessary at this point, a few GPUs will do the job.",
        "PAM: Account locked for 3 years.",
        "Some cause happiness wherever they go; others whenever they go.",
        "Why do you sit there looking like an envelope without any address on it?",
        "You wasted valuable CPU time with this non-sense.",
        "Time to use a password manager, dummy.",
        "Eww, what a nasty password. Access denied!",
        "You do that again and see what happens...",
        "Pathetic!"
};

#endif // INSULTS_H