/*
 * Pneuma - Dual Mode Quote App
 * Death Note & Boondocks modes with dynamic backgrounds
 * Compile: gcc -o pneuma pneuma.c `pkg-config --cflags --libs gtk+-3.0 gdk-pixbuf-2.0` -lm
 */

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

// Mode definitions
#define MODE_DEATH_NOTE 0
#define MODE_BOONDOCKS 1

// Application data structure
typedef struct {
    GtkWidget *window;
    GtkWidget *quote_label;
    GtkWidget *author_label;
    GtkWidget *mode_label;
    GtkWidget *next_button;
    GtkWidget *mode_button;
    GtkWidget *exit_button;
    int current_mode;
    int current_bg_index;
    char **deathnote_images;
    char **boondocks_images;
    int deathnote_count;
    int boondocks_count;
} AppData;

// Death Note quotes
typedef struct {
    char *text;
    char *author;
} Quote;
Quote deathnote_quotes[] = {
    {"I am justice! I am the one who will become the god of the new world!", "Light Yagami"},
    {"I'll take a potato chip... AND EAT IT!", "Light Yagami"},
    {"Humans are all the same. They all think they're special.", "L"},
    {"There is no heaven or hell. No matter what you do while you're alive, everyone goes to the same place once they die.", "Souichiro Yagami"},
    {"The only one who can kill me is myself.", "Light Yagami"},
    {"I'm not a god. I'm just a human who happened to pick up a Death Note.", "Light Yagami"},
    {"Justice is a matter of perspective.", "L"},
    {"Fear is necessary for evolution.", "L"},
    {"I am the god of the new world!", "Light Yagami"},
    {"If you use the Death Note, you cannot go to heaven or hell.", "Ryuk"},
    {"The human whose name is written in this note shall die.", "Death Note Rule"},
    {"L, do you know gods of death love apples?", "Ryuk"},
    {"Kira is evil. I will stop him.", "L"},
    {"I am Kira. I will be the god of this new world.", "Light Yagami"},
    {"The one who uses the Death Note will neither go to heaven nor hell.", "Ryuk"},
    {"I'm not going to lose to someone who doesn't even believe in justice.", "Light Yagami"},
    {"L, you are not going to die. I am going to kill you.", "Light Yagami"},
    {"I am the one who will become the god of the new world.", "Light Yagami"},
    {"If I win, I am justice. If you win, you are justice.", "Light Yagami"},
    {"There are many types of monsters in this world.", "L"},
    {"I am just a passing through Kira. Remember that!", "Light Yagami"},
    {"The world is rotten. Those who are making it rotten should be removed.", "Light Yagami"},
    {"I am not a god. I am just a human who picked up a Death Note.", "Light Yagami"},
    {"Light, I have a feeling you are going to be the one who saves mankind.", "Souichiro Yagami"},
    {"The only way to win is to be smarter than your opponent.", "L"},
    {"I don't want to die. I want to live. I want to see the world I created.", "Light Yagami"},
    {"My name is Light Yagami. I am Kira.", "Light Yagami"},
    {"I will become the god of the new world.", "Light Yagami"},
    {"The game has just begun.", "L"},
    {"You can't win a game of chess if you don't know the rules.", "L"},
    {"I am justice. I protect the innocent from evil.", "Light Yagami"},
    {"The only way to defeat me is to become me.", "Light Yagami"},
    {"I will cleanse the world of evil.", "Light Yagami"},
    {"The Death Note has no effect on anyone under 780 days old.", "Death Note Rule"},
    {"If you miss, I will find you.", "L"},
    {"I am not a killer. I am a god.", "Light Yagami"},
    {"The world needs a god. I will be that god.", "Light Yagami"},
    {"I am the one who will change the world.", "Light Yagami"},
    {"Justice always wins. That's why I will win.", "Light Yagami"},
    {"I am the new world's god.", "Light Yagami"},
    {"The only one who can judge me is myself.", "Light Yagami"},
    {"I will create a perfect world.", "Light Yagami"},
    {"I am the one who will bring true justice.", "Light Yagami"},
    {"The world is full of evil. I will fix it.", "Light Yagami"},
    {"I am the chosen one.", "Light Yagami"},
    {"God is dead. I am the new god.", "Light Yagami"},
    {"I will not lose to anyone.", "Light Yagami"},
    {"This is the beginning of a new era.", "Light Yagami"},
    {"I am the light in the darkness.", "Light Yagami"},
    {"I will be the hope of the people.", "Light Yagami"},
    {"The world will be mine.", "Light Yagami"}
};


// Boondocks quotes
Quote boondocks_quotes[] = {
    {"I am the truth! I am the light! I am the one!", "Huey Freeman"},
    {"The revolution will not be televised.", "Huey Freeman"},
    {"Granddad, you ain't never too old to learn.", "Riley Freeman"},
    {"I'm just trying to be a good person.", "Huey Freeman"},
    {"Sometimes you gotta do what you gotta do.", "Robert Freeman"},
    {"That's the problem with you niggas. You don't read.", "Huey Freeman"},
    {"I'm a thug. I'm a gangsta. I'm a warrior.", "Riley Freeman"},
    {"Knowledge is power. The more you know, the more you can fight.", "Huey Freeman"},
    {"Freedom is not given. It is taken.", "Huey Freeman"},
    {"The system is designed to keep us down.", "Huey Freeman"},
    {"I'm not angry. I'm just disappointed.", "Robert Freeman"},
    {"That's what you get for being a fool.", "Riley Freeman"},
    {"The truth is like a lion. You don't have to defend it.", "Huey Freeman"},
    {"Wake up, people! The revolution is here!", "Huey Freeman"},
    {"They brainwashed you. You gotta wake up.", "Huey Freeman"},
    {"Money can't buy happiness, but it can buy you a better class of misery.", "Robert Freeman"},
    {"I'm not a slave to nobody.", "Huey Freeman"},
    {"The white man is the devil.", "Uncle Ruckus"},
    {"I'm 106 percent African American!", "Uncle Ruckus"},
    {"Re-volution! Re-volution!", "Riley Freeman"},
    {"I don't have a dream. I have a plan.", "Huey Freeman"},
    {"The American dream is a nightmare.", "Huey Freeman"},
    {"They want us to be ignorant so they can control us.", "Huey Freeman"},
    {"Education is the key to freedom.", "Huey Freeman"},
    {"You can't trust anyone in this world.", "Riley Freeman"},
    {"I'm the baddest mutha out there!", "Riley Freeman"},
    {"Granddad, you trippin'!", "Riley Freeman"},
    {"I'm gonna be rich, famous, and powerful!", "Riley Freeman"},
    {"You gotta get that paper, son!", "Riley Freeman"},
    {"I'm about to get that money!", "Riley Freeman"},
    {"The struggle is real.", "Huey Freeman"},
    {"They don't want us to succeed.", "Huey Freeman"},
    {"We gotta rise up!", "Huey Freeman"},
    {"I ain't never had nothing. Now I got something.", "Robert Freeman"},
    {"Back in my day, we had respect!", "Robert Freeman"},
    {"These kids today don't know nothing.", "Robert Freeman"},
    {"I told you not to mess with that!", "Robert Freeman"},
    {"You gonna learn today!", "Robert Freeman"},
    {"I'm the king of this house!", "Robert Freeman"},
    {"My ancestors didn't die for this!", "Huey Freeman"},
    {"We stand on the shoulders of giants.", "Huey Freeman"},
    {"The fight continues.", "Huey Freeman"},
    {"Never give up. Never surrender.", "Huey Freeman"},
    {"One day, things will change.", "Huey Freeman"},
    {"Keep fighting the good fight.", "Huey Freeman"},
    {"The revolution is inside you.", "Huey Freeman"},
    {"Be the change you want to see.", "Huey Freeman"},
    {"Knowledge is the only weapon.", "Huey Freeman"},
    {"Stay woke, my friends.", "Huey Freeman"},
    {"The truth will set you free.", "Huey Freeman"}
};

// Powerful general quotes
Quote general_quotes[] = {
    {"The only way to do great work is to love what you do.", "Steve Jobs"},
    {"Success is not final, failure is not fatal.", "Winston Churchill"},
    {"Believe you can and you're halfway there.", "Theodore Roosevelt"},
    {"It always seems impossible until it's done.", "Nelson Mandela"},
    {"The future belongs to those who believe in the beauty of their dreams.", "Eleanor Roosevelt"},
    {"Your time is limited, don't waste it living someone else's life.", "Steve Jobs"},
    {"The only limit to our realization of tomorrow is our doubts of today.", "Franklin D. Roosevelt"},
    {"Strive not to be a success, but rather to be of value.", "Albert Einstein"},
    {"The mind is everything. What you think you become.", "Buddha"},
    {"Darkness cannot drive out darkness; only light can do that.", "Martin Luther King Jr."},
    {"The best time to plant a tree was 20 years ago. The second best time is now.", "Chinese Proverb"},
    {"What you get by achieving your goals is not as important as what you become.", "Zig Ziglar"},
    {"Life is what happens when you're busy making other plans.", "John Lennon"},
    {"The purpose of our lives is to be happy.", "Dalai Lama"},
    {"The journey of a thousand miles begins with a single step.", "Lao Tzu"},
    {"Fall seven times, stand up eight.", "Japanese Proverb"},
    {"Hardships often prepare ordinary people for an extraordinary destiny.", "C.S. Lewis"},
    {"The greatest glory in living lies not in never falling, but in rising every time we fall.", "Nelson Mandela"},
    {"The way to get started is to quit talking and begin doing.", "Walt Disney"},
    {"If life were predictable it would cease to be life, and be without flavor.", "Eleanor Roosevelt"},
    {"Life is either a daring adventure or nothing at all.", "Helen Keller"},
    {"The greatest wealth is to live content with little.", "Plato"},
    {"Happiness is not something readymade. It comes from your own actions.", "Dalai Lama"},
    {"The only source of knowledge is experience.", "Albert Einstein"},
    {"Imagination is more important than knowledge.", "Albert Einstein"},
    {"The secret of getting ahead is getting started.", "Mark Twain"},
    {"Don't watch the clock; do what it does. Keep going.", "Sam Levenson"},
    {"The harder I work, the luckier I get.", "Samuel Goldwyn"},
    {"There are no shortcuts to any place worth going.", "Beverly Sills"},
    {"Success is walking from failure to failure with no loss of enthusiasm.", "Winston Churchill"},
    {"I find that the harder I work, the more luck I seem to have.", "Thomas Jefferson"},
    {"Success usually comes to those who are too busy to be looking for it.", "Henry David Thoreau"},
    {"Opportunity is missed by most people because it is dressed in overalls and looks like work.", "Thomas Edison"},
    {"The only place where success comes before work is in the dictionary.", "Vidal Sassoon"},
    {"The secret of success is to do the common thing uncommonly well.", "John D. Rockefeller Jr."},
    {"Success is not in what you have, but who you are.", "Bo Bennett"},
    {"Success is how high you bounce when you hit bottom.", "George S. Patton"},
    {"Success is liking yourself, liking what you do, and liking how you do it.", "Maya Angelou"},
    {"Success is not the key to happiness. Happiness is the key to success.", "Albert Schweitzer"},
    {"The only limit to our realization of tomorrow is our doubts of today.", "Franklin D. Roosevelt"},
    {"It does not matter how slowly you go as long as you do not stop.", "Confucius"},
    {"Everything you've ever wanted is on the other side of fear.", "George Addair"},
    {"Dream it. Wish it. Do it.", "Unknown"},
    {"Keep your face always toward the sunshine—and shadows will fall behind you.", "Walt Whitman"},
    {"You are never too old to set another goal or to dream a new dream.", "C.S. Lewis"},
    {"Don't be pushed around by the fears in your mind. Be led by the dreams in your heart.", "Roy T. Bennett"},
    {"The only person you are destined to become is the person you decide to be.", "Ralph Waldo Emerson"},
    {"What lies behind us and what lies before us are tiny matters compared to what lies within us.", "Ralph Waldo Emerson"},
    {"The future depends on what you do today.", "Mahatma Gandhi"},
    {"You must be the change you wish to see in the world.", "Mahatma Gandhi"},
    {"First they ignore you, then they laugh at you, then they fight you, then you win.", "Mahatma Gandhi"},
    {"Be the change that you wish to see in the world.", "Mahatma Gandhi"},
    {"Live as if you were to die tomorrow. Learn as if you were to live forever.", "Mahatma Gandhi"},
    {"The weak can never forgive. Forgiveness is the attribute of the strong.", "Mahatma Gandhi"},
    {"Strength does not come from physical capacity. It comes from an indomitable will.", "Mahatma Gandhi"},
    {"You may never know what results come of your actions, but if you do nothing, there will be no result.", "Mahatma Gandhi"},
    {"Happiness is when what you think, what you say, and what you do are in harmony.", "Mahatma Gandhi"},
    {"In a gentle way, you can shake the world.", "Mahatma Gandhi"},
    {"The best way to find yourself is to lose yourself in the service of others.", "Mahatma Gandhi"},
    {"To believe in something, and not to live it, is dishonest.", "Mahatma Gandhi"},
    {"Action expresses priorities.", "Mahatma Gandhi"},
    {"Where there is love, there is life.", "Mahatma Gandhi"},
    {"The difference between what we do and what we are capable of doing would suffice to solve most of the world's problems.", "Mahatma Gandhi"},
    {"I will not let anyone walk through my mind with their dirty feet.", "Mahatma Gandhi"},
    {"Nobody can hurt me without my permission.", "Mahatma Gandhi"},
    {"The greatness of a nation and its moral progress can be judged by the way its animals are treated.", "Mahatma Gandhi"},
    {"A man is but the product of his thoughts. What he thinks, he becomes.", "Mahatma Gandhi"},
    {"There is more to life than increasing its speed.", "Mahatma Gandhi"},
    {"It is health that is real wealth and not pieces of gold and silver.", "Mahatma Gandhi"},
    {"The future is something which everyone reaches at the rate of sixty minutes an hour, whatever he does, whoever he is.", "C.S. Lewis"},
    {"You can't go back and change the beginning, but you can start where you are and change the ending.", "C.S. Lewis"},
    {"Friendship is born at that moment when one person says to another, 'What! You too? I thought I was the only one.'", "C.S. Lewis"},
    {"There are far, far better things ahead than any we leave behind.", "C.S. Lewis"},
    {"You can make anything by writing.", "C.S. Lewis"},
    {"Courage, dear heart.", "C.S. Lewis"},
    {"We are what we believe we are.", "C.S. Lewis"},
    {"The greatest adventure is what lies ahead.", "J.R.R. Tolkien"},
    {"All we have to decide is what to do with the time that is given us.", "J.R.R. Tolkien"},
    {"Even the smallest person can change the course of the future.", "J.R.R. Tolkien"},
    {"Not all those who wander are lost.", "J.R.R. Tolkien"},
    {"Faithless is he that says farewell when the road darkens.", "J.R.R. Tolkien"},
    {"I will not say: do not weep; for not all tears are an evil.", "J.R.R. Tolkien"},
    {"A single dream is more powerful than a thousand realities.", "J.R.R. Tolkien"},
    {"The world is indeed full of peril, and in it there are many dark places; but still there is much that is fair.", "J.R.R. Tolkien"},
    {"It's the job that's never started as takes longest to finish.", "J.R.R. Tolkien"},
    {"Short cuts make long delays.", "J.R.R. Tolkien"},
    {"There is nothing like looking, if you want to find something.", "J.R.R. Tolkien"},
    {"Home is behind, the world ahead.", "J.R.R. Tolkien"},
    {"The road goes ever on and on.", "J.R.R. Tolkien"},
    {"Where there's life, there's hope.", "J.R.R. Tolkien"},
    {"The wise speak only of what they know.", "J.R.R. Tolkien"},
    {"A man that flies from his fear may find that he has only taken a short cut to meet it.", "J.R.R. Tolkien"},
    {"Do not be too eager to deal out death in judgment.", "J.R.R. Tolkien"},
    {"In the end, it's not the years in your life that count. It's the life in your years.", "Abraham Lincoln"},
    {"Whatever you are, be a good one.", "Abraham Lincoln"},
    {"I am a slow walker, but I never walk back.", "Abraham Lincoln"},
    {"Most folks are as happy as they make up their minds to be.", "Abraham Lincoln"},
    {"The best way to predict your future is to create it.", "Abraham Lincoln"},
    {"Give me six hours to chop down a tree and I will spend the first four sharpening the axe.", "Abraham Lincoln"},
    {"My great concern is not whether you have failed, but whether you are content with your failure.", "Abraham Lincoln"},
    {"The greatest glory in living lies not in never falling, but in rising every time we fall.", "Abraham Lincoln"},
    {"Always bear in mind that your own resolution to succeed is more important than any other.", "Abraham Lincoln"},
    {"Character is like a tree and reputation like its shadow. The shadow is what we think of it; the tree is the real thing.", "Abraham Lincoln"},
    {"I will prepare and some day my chance will come.", "Abraham Lincoln"},
    {"The best thing about the future is that it comes one day at a time.", "Abraham Lincoln"},
    {"The way to be happy is to be happy.", "Abraham Lincoln"},
    {"If you want to test a man's character, give him power.", "Abraham Lincoln"},
    {"Nearly all men can stand adversity, but if you want to test a man's character, give him power.", "Abraham Lincoln"},
    {"Tact is the ability to describe others as they see themselves.", "Abraham Lincoln"},
    {"I don't like that man. I must get to know him better.", "Abraham Lincoln"},
    {"No man has a good enough memory to be a successful liar.", "Abraham Lincoln"},
    {"You cannot escape the responsibility of tomorrow by evading it today.", "Abraham Lincoln"},
    {"I'm a success today because I had a friend who believed in me and I didn't have the heart to let him down.", "Abraham Lincoln"},
    {"It's not the years in your life that count. It's the life in your years.", "Abraham Lincoln"},
    {"The time is always right to do what is right.", "Martin Luther King Jr."},
    {"Faith is taking the first step even when you don't see the whole staircase.", "Martin Luther King Jr."},
    {"I have decided to stick with love. Hate is too great a burden to bear.", "Martin Luther King Jr."},
    {"The ultimate measure of a man is not where he stands in moments of comfort and convenience, but where he stands at times of challenge and controversy.", "Martin Luther King Jr."},
    {"Injustice anywhere is a threat to justice everywhere.", "Martin Luther King Jr."},
    {"Our lives begin to end the day we become silent about things that matter.", "Martin Luther King Jr."},
    {"The time is always right to do what is right.", "Martin Luther King Jr."},
    {"We must accept finite disappointment, but never lose infinite hope.", "Martin Luther King Jr."},
    {"Love is the only force capable of transforming an enemy into a friend.", "Martin Luther King Jr."},
    {"I look to a day when people will not be judged by the color of their skin, but by the content of their character.", "Martin Luther King Jr."},
    {"Peace is not merely a distant goal that we seek, but a means by which we arrive at that goal.", "Martin Luther King Jr."},
    {"The arc of the moral universe is long, but it bends toward justice.", "Martin Luther King Jr."},
    {"We may have all come on different ships, but we're in the same boat now.", "Martin Luther King Jr."},
    {"Whatever your life's work is, do it well.", "Martin Luther King Jr."},
    {"If you can't fly then run, if you can't run then walk, if you can't walk then crawl, but whatever you do you have to keep moving forward.", "Martin Luther King Jr."},
    {"Only in the darkness can you see the stars.", "Martin Luther King Jr."},
    {"There is no gain without struggle.", "Martin Luther King Jr."},
    {"Change does not roll in on the wheels of inevitability, but comes through continuous struggle.", "Martin Luther King Jr."},
    {"We must build dikes of courage to hold back the flood of fear.", "Martin Luther King Jr."},
    {"The quality, not the longevity, of one's life is what is important.", "Martin Luther King Jr."},
    {"Everything that is done in the world is done by hope.", "Martin Luther King Jr."},
    {"A genuine leader is not a searcher for consensus but a molder of consensus.", "Martin Luther King Jr."},
    {"There comes a time when one must take a position that is neither safe, nor politic, nor popular, but he must take it because conscience tells him it is right.", "Martin Luther King Jr."},
    {"Never, never be afraid to do what's right, especially if the well-being of a person or animal is at stake.", "Martin Luther King Jr."},
    {"The time is always right to do what is right.", "Martin Luther King Jr."},
    {"To be a Christian without prayer is no more possible than to be alive without breathing.", "Martin Luther King Jr."},
    {"We must use time creatively.", "Martin Luther King Jr."},
    {"A man who won't die for something is not fit to live.", "Martin Luther King Jr."},
    {"I am not interested in power for power's sake, but I'm interested in power that is moral, that is right and that is good.", "Martin Luther King Jr."},
    {"One of the great liabilities of life is that all too many people find themselves living amid a great period of social change, and yet they fail to develop the new attitudes, the new mental responses, that the new situation requires.", "Martin Luther King Jr."},
    {"The hope of a secure and livable world lies with disciplined nonconformists who are dedicated to justice, peace and brotherhood.", "Martin Luther King Jr."},
    {"The ultimate tragedy is not the oppression and cruelty by the bad people but the silence over that by the good people.", "Martin Luther King Jr."},
    {"I have a dream that one day every valley shall be exalted, every hill and mountain shall be made low, the rough places will be made straight and the glory of the Lord shall be revealed and all flesh shall see it together.", "Martin Luther King Jr."},
    {"I have a dream that my four little children will one day live in a nation where they will not be judged by the color of their skin but by the content of their character.", "Martin Luther King Jr."},
    {"Let no man pull you so low as to hate him.", "Martin Luther King Jr."},
    {"Life's most persistent and urgent question is, 'What are you doing for others?'", "Martin Luther King Jr."},
    {"We must live together as brothers or perish together as fools.", "Martin Luther King Jr."},
    {"The time is always right to do what is right.", "Martin Luther King Jr."},
    {"There is no such thing as being too late in life to become the person you want to be.", "Martin Luther King Jr."},
    {"A lie cannot live.", "Martin Luther King Jr."},
    {"Our scientific power has outrun our spiritual power. We have guided missiles and misguided men.", "Martin Luther King Jr."},
    {"I want to be the white man's brother, not his brother-in-law.", "Martin Luther King Jr."},
    {"All progress is precarious, and the solution of one problem brings us face to face with another problem.", "Martin Luther King Jr."},
    {"The moral arc of the universe is long, but it bends toward justice.", "Martin Luther King Jr."}
};
 

#define DEATHNOTE_QUOTE_COUNT (sizeof(deathnote_quotes) / sizeof(Quote))
#define BOONDOCKS_QUOTE_COUNT (sizeof(boondocks_quotes) / sizeof(Quote))
#define GENERAL_QUOTE_COUNT (sizeof(general_quotes) / sizeof(Quote))

// Function to get random quote based on mode
Quote get_random_quote(AppData *app) {
    int total_quotes;
    int idx;
    
    if (app->current_mode == MODE_DEATH_NOTE) {
        total_quotes = DEATHNOTE_QUOTE_COUNT + GENERAL_QUOTE_COUNT;
        idx = rand() % total_quotes;
        if (idx < DEATHNOTE_QUOTE_COUNT) {
            return deathnote_quotes[idx];
        } else {
            return general_quotes[idx - DEATHNOTE_QUOTE_COUNT];
        }
    } else {
        total_quotes = BOONDOCKS_QUOTE_COUNT + GENERAL_QUOTE_COUNT;
        idx = rand() % total_quotes;
        if (idx < BOONDOCKS_QUOTE_COUNT) {
            return boondocks_quotes[idx];
        } else {
            return general_quotes[idx - BOONDOCKS_QUOTE_COUNT];
        }
    }
}

// Function to load images from directory
char** load_images(const char *path, int *count) {
    DIR *dir;
    struct dirent *entry;
    char **images = NULL;
    int num = 0;
    
    dir = opendir(path);
    if (!dir) {
        *count = 0;
        return NULL;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *ext = strrchr(entry->d_name, '.');
            if (ext && (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || 
                        strcmp(ext, ".png") == 0)) {
                char *fullpath = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(fullpath, "%s/%s", path, entry->d_name);
                images = realloc(images, (num + 1) * sizeof(char*));
                images[num] = fullpath;
                num++;
            }
        }
    }
    
    closedir(dir);
    *count = num;
    return images;
}

// Function to set background image
void set_background_image(GtkWidget *window, const char *image_path) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_path, NULL);
    if (!pixbuf) return;
    
    // Get screen dimensions
    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen);
    int height = gdk_screen_get_height(screen);
    
    // Scale image to window size
    GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf);
    
    // Create CSS with background image
    char css[2048];
    snprintf(css, sizeof(css),
        "window { "
        "   background-image: url('%s'); "
        "   background-size: cover; "
        "   background-repeat: no-repeat; "
        "   background-position: center; "
        "}"
        "label { "
        "   color: #ffffff; "
        "   text-shadow: 0 2px 10px rgba(0,0,0,0.8); "
        "}"
        "button { "
        "   background: rgba(0,0,0,0.6); "
        "   border: 1px solid rgba(255,255,255,0.3); "
        "   border-radius: 25px; "
        "   color: #ffffff; "
        "   padding: 10px 24px; "
        "   font-weight: bold; "
        "   font-size: 14px; "
        "}"
        "button:hover { "
        "   background: rgba(0,0,0,0.8); "
        "   border-color: #ff6b6b; "
        "}",
        image_path);
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    g_object_unref(provider);
    g_object_unref(scaled);
}

// Function to change background based on mode
void change_background(AppData *app) {
    char **images;
    int count;
    
    if (app->current_mode == MODE_DEATH_NOTE) {
        images = app->deathnote_images;
        count = app->deathnote_count;
    } else {
        images = app->boondocks_images;
        count = app->boondocks_count;
    }
    
    if (count > 0) {
        app->current_bg_index = (app->current_bg_index + 1) % count;
        set_background_image(app->window, images[app->current_bg_index]);
    }
}

// Function to update quote with changing text colors
void update_quote(AppData *app) {
    Quote quote = get_random_quote(app);
    char markup[2048];
    char quote_color[20], author_color[20];
    
    // Set colors based on mode
    if (app->current_mode == MODE_DEATH_NOTE) {
        strcpy(quote_color, "#ff6b6b");
        strcpy(author_color, "#ff8c8c");
    } else {
        strcpy(quote_color, "#4ecdc4");
        strcpy(author_color, "#6ee7df");
    }
    
    // Randomly choose text color variation for visual interest
    int variation = rand() % 3;
    if (variation == 0) {
        // Keep as is
    } else if (variation == 1) {
        // Lighter variation
        if (app->current_mode == MODE_DEATH_NOTE) {
            strcpy(quote_color, "#ff8787");
            strcpy(author_color, "#ffaaaa");
        } else {
            strcpy(quote_color, "#6ee7df");
            strcpy(author_color, "#8ff3ec");
        }
    } else {
        // Golden variation for emphasis
        strcpy(quote_color, "#ffd966");
        strcpy(author_color, "#ffe69e");
    }
    
    // Set quote text with colored font
    snprintf(markup, sizeof(markup), 
             "<span size='x-large' weight='bold' foreground='%s'>%s</span>", 
             quote_color, quote.text);
    gtk_label_set_markup(GTK_LABEL(app->quote_label), markup);
    
    // Set author with matching color
    snprintf(markup, sizeof(markup), 
             "<span size='large' foreground='%s'>— %s —</span>", 
             author_color, quote.author);
    gtk_label_set_markup(GTK_LABEL(app->author_label), markup);
    
    // Update mode label with accent colors
    if (app->current_mode == MODE_DEATH_NOTE) {
        gtk_label_set_markup(GTK_LABEL(app->mode_label), 
                             "<span size='small' weight='bold' foreground='#ff6b6b'>DEATH NOTE MODE</span>");
    } else {
        gtk_label_set_markup(GTK_LABEL(app->mode_label), 
                             "<span size='small' weight='bold' foreground='#4ecdc4'>BOONDOCKS MODE</span>");
    }
}

// Button callbacks
void on_next_clicked(GtkWidget *widget, AppData *app) {
    (void)widget;
    change_background(app);
    update_quote(app);
}

void on_mode_clicked(GtkWidget *widget, AppData *app) {
    (void)widget;
    if (app->current_mode == MODE_DEATH_NOTE) {
        app->current_mode = MODE_BOONDOCKS;
    } else {
        app->current_mode = MODE_DEATH_NOTE;
    }
    app->current_bg_index = -1;
    change_background(app);
    update_quote(app);
}

void on_exit_clicked(GtkWidget *widget, AppData *app) {
    (void)widget;
    (void)app;
    gtk_main_quit();
}

// Function to create initial mode selection dialog
int show_mode_selection(GtkWidget *parent) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *button_box;
    GtkWidget *deathnote_btn;
    GtkWidget *boondocks_btn;
    GtkWidget *label;
    int result = MODE_DEATH_NOTE;
    
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "pneuma - Select Mode");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 250);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
    
    // Set window icon
    char icon_path[512];
    snprintf(icon_path, sizeof(icon_path), "%s/pneuma/icon.png", getenv("HOME"));
    GdkPixbuf *icon = gdk_pixbuf_new_from_file(icon_path, NULL);
    if (icon) {
        gtk_window_set_icon(GTK_WINDOW(dialog), icon);
        g_object_unref(icon);
    }
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 20);
    
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), 
                         "<span size='x-large' weight='bold'>choose your path</span>");
    gtk_box_pack_start(GTK_BOX(content_area), label, FALSE, FALSE, 10);
    
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), 
                         "<span>select the theme for your journey</span>");
    gtk_box_pack_start(GTK_BOX(content_area), label, FALSE, FALSE, 5);
    
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_widget_set_halign(button_box, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(content_area), button_box, TRUE, TRUE, 20);
    
    deathnote_btn = gtk_button_new_with_label("DEATH NOTE");
    gtk_widget_set_size_request(deathnote_btn, 150, 50);
    g_signal_connect(deathnote_btn, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
    g_signal_connect(deathnote_btn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), deathnote_btn, FALSE, FALSE, 0);
    
    boondocks_btn = gtk_button_new_with_label("BOONDOCKS");
    gtk_widget_set_size_request(boondocks_btn, 150, 50);
    g_signal_connect(boondocks_btn, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
    g_signal_connect(boondocks_btn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), boondocks_btn, FALSE, FALSE, 0);
    
    // Connect to get response
    g_signal_connect(deathnote_btn, "clicked", G_CALLBACK(gtk_dialog_response), 
                     GINT_TO_POINTER(MODE_DEATH_NOTE));
    g_signal_connect(boondocks_btn, "clicked", G_CALLBACK(gtk_dialog_response), 
                     GINT_TO_POINTER(MODE_BOONDOCKS));
    
    gtk_widget_show_all(dialog);
    
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response >= 0) {
        result = response;
    }
    gtk_widget_destroy(dialog);
    
    return result;
}

// Main function
int main(int argc, char *argv[]) {
    AppData *app;
    GtkWidget *main_box, *top_box, *bottom_box;
    GtkWidget *title;
    GtkWidget *next_btn, *mode_btn, *exit_btn;
    GtkWidget *center_box;
    char home_dir[512];
    
    // Initialize
    srand(time(NULL));
    gtk_init(&argc, &argv);
    
    // Allocate app data
    app = g_malloc0(sizeof(AppData));
    app->current_bg_index = -1;
    
    // Get home directory
    snprintf(home_dir, sizeof(home_dir), "%s/pneuma", getenv("HOME"));
    
    // Load images
    char deathnote_path[512], boondocks_path[512];
    snprintf(deathnote_path, sizeof(deathnote_path), "%s/deathnote", home_dir);
    snprintf(boondocks_path, sizeof(boondocks_path), "%s/boondocks", home_dir);
    
    app->deathnote_images = load_images(deathnote_path, &app->deathnote_count);
    app->boondocks_images = load_images(boondocks_path, &app->boondocks_count);
    
    // Create main window
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "pneuma");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 800, 500);
    gtk_window_set_position(GTK_WINDOW(app->window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(app->window), 30);
    
    // Set window icon
    char icon_path[512];
    snprintf(icon_path, sizeof(icon_path), "%s/icon.png", home_dir);
    GdkPixbuf *icon = gdk_pixbuf_new_from_file(icon_path, NULL);
    if (icon) {
        gtk_window_set_icon(GTK_WINDOW(app->window), icon);
        g_object_unref(icon);
    }
    
    // Set dark theme preference
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
    
    // Create main container
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(app->window), main_box);
    
    // Top section with title and mode
    top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(main_box), top_box, FALSE, FALSE, 0);
    
    title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), 
                         "<span size='xx-large' weight='bold'>pneuma</span>");
    gtk_box_pack_start(GTK_BOX(top_box), title, TRUE, TRUE, 0);
    
    // Mode label
    app->mode_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(app->mode_label), 
                         "<span size='small' weight='bold'>DEATH NOTE MODE</span>");
    gtk_box_pack_start(GTK_BOX(top_box), app->mode_label, FALSE, FALSE, 0);
    
    // Center section with quote
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_halign(center_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(center_box, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), center_box, TRUE, TRUE, 0);
    
    // Quote label
    app->quote_label = gtk_label_new(NULL);
    gtk_label_set_line_wrap(GTK_LABEL(app->quote_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(app->quote_label), GTK_WRAP_WORD);
    gtk_label_set_max_width_chars(GTK_LABEL(app->quote_label), 60);
    gtk_widget_set_halign(app->quote_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(app->quote_label, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(center_box), app->quote_label, TRUE, TRUE, 0);
    
    // Author label
    app->author_label = gtk_label_new(NULL);
    gtk_widget_set_halign(app->author_label, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(center_box), app->author_label, FALSE, FALSE, 0);
    
    // Bottom section with buttons
    bottom_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_widget_set_halign(bottom_box, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), bottom_box, FALSE, FALSE, 20);
    
    // Next button
    next_btn = gtk_button_new_with_label("next");
    gtk_widget_set_size_request(next_btn, 120, 45);
    g_signal_connect(next_btn, "clicked", G_CALLBACK(on_next_clicked), app);
    gtk_box_pack_start(GTK_BOX(bottom_box), next_btn, FALSE, FALSE, 0);
    
    // Mode button
    mode_btn = gtk_button_new_with_label("switch mode");
    gtk_widget_set_size_request(mode_btn, 140, 45);
    g_signal_connect(mode_btn, "clicked", G_CALLBACK(on_mode_clicked), app);
    gtk_box_pack_start(GTK_BOX(bottom_box), mode_btn, FALSE, FALSE, 0);
    
    // Exit button
    exit_btn = gtk_button_new_with_label("exit");
    gtk_widget_set_size_request(exit_btn, 100, 45);
    g_signal_connect(exit_btn, "clicked", G_CALLBACK(on_exit_clicked), app);
    gtk_box_pack_start(GTK_BOX(bottom_box), exit_btn, FALSE, FALSE, 0);
    
    // Show mode selection on first run
    char config_path[512];
    snprintf(config_path, sizeof(config_path), "%s/.pneuma_mode", getenv("HOME"));
    FILE *config = fopen(config_path, "r");
    
    if (config) {
        int saved_mode;
        fscanf(config, "%d", &saved_mode);
        app->current_mode = saved_mode;
        fclose(config);
    } else {
        app->current_mode = show_mode_selection(app->window);
        config = fopen(config_path, "w");
        if (config) {
            fprintf(config, "%d", app->current_mode);
            fclose(config);
        }
    }
    
    // Set initial background and quote
    change_background(app);
    update_quote(app);
    
    // Connect destroy signal
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Show window
    gtk_widget_show_all(app->window);
    
    // Start main loop
    gtk_main();
    
    // Cleanup
    for (int i = 0; i < app->deathnote_count; i++) free(app->deathnote_images[i]);
    for (int i = 0; i < app->boondocks_count; i++) free(app->boondocks_images[i]);
    free(app->deathnote_images);
    free(app->boondocks_images);
    g_free(app);
    
    return 0;
}
