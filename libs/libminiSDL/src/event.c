#include <NDL.h>
#include <SDL.h>
#include <string.h>
#include <stdio.h>

#define keyname(k) #k,


static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

#define NR_KEYS (sizeof(keyname) / sizeof(keyname[0]))

static uint8_t keystate[NR_KEYS] = {0};

int SDL_PushEvent(SDL_Event *ev) {

 char buf[64];
  if (NDL_PollEvent(buf, sizeof(buf)) == 0) return 0;

  char type[4], name[32];
  sscanf(buf, "%s %s", type, name);
  for (int i = 0; i < sizeof(keyname) / sizeof(keyname[0]); i++) {
    if (strcmp(name, keyname[i]) == 0) {
      ev->type = (type[1] == 'd') ? SDL_KEYDOWN : SDL_KEYUP;
      ev->key.keysym.sym = i;
      keystate[i] = (ev->type == SDL_KEYDOWN);
      return 1;
    }
  }
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
   char buf[64];
  if (NDL_PollEvent(buf, sizeof(buf)) == 0) return 0;

  char type[8], name[32];
  if (sscanf(buf, "%7s %31s", type, name) != 2) return 0;

  for (int i = 0; i < NR_KEYS; i++) {
    if (strcmp(name, keyname[i]) == 0) {
      ev->type = (type[1] == 'd') ? SDL_KEYDOWN : SDL_KEYUP;
      ev->key.keysym.sym = i;
      keystate[i] = (ev->type == SDL_KEYDOWN);
      return 1;
    }
  }
  return 0;
}

int SDL_WaitEvent(SDL_Event *event) {
    while (SDL_PollEvent(event) == 0) ;
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
   if (numkeys) *numkeys = sizeof(keystate);
  return keystate;
}
