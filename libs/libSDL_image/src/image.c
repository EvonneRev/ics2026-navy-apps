#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SDL_malloc  malloc
#define SDL_free    free
#define SDL_realloc realloc

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
  assert(src->type == RW_TYPE_MEM);
  assert(freesrc == 0);
  return NULL;
}

SDL_Surface* IMG_Load(const char *filename) {
   FILE *fp = fopen(filename, "rb");
  if (!fp) return NULL;

  SDL_Surface *surface = NULL;
  if (fseek(fp, 0, SEEK_END) == 0) {
    long len = ftell(fp);
    if (len > 0 && len <= INT_MAX && fseek(fp, 0, SEEK_SET) == 0) {
      unsigned char *buf = malloc((size_t)len);
      if (buf) {
        if (fread(buf, 1, (size_t)len, fp) == (size_t)len) {
          surface = STBIMG_LoadFromMemory(buf, (int)len);
        }
        free(buf);
      }
    }
  }
  fclose(fp);
  return surface;
}

int IMG_isPNG(SDL_RWops *src) {
  return 0;
}

SDL_Surface* IMG_LoadJPG_RW(SDL_RWops *src) {
   assert(src->type == RW_TYPE_MEM);
  assert(free == 0);
  return NULL;  // ← 这里需要实现
}

char *IMG_GetError() {
  return "Navy does not support IMG_GetError()";
}
