#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define API_KEY "dcfb25370d16c862e558fda8422ec8eb"
#define API_URL "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    printf("Not enough memory to store data.\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void fetch_weather_data(char *location, struct MemoryStruct *chunk) {
  CURL *curl_handle;
  CURLcode res;

  chunk->memory = malloc(1);
  chunk->size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  char url[256];
  sprintf(url, API_URL, location, API_KEY);

  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);

  res = curl_easy_perform(curl_handle);

  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }

  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();
}

void parse_weather_data(struct MemoryStruct *chunk) {
  struct json_object *json_obj;
  struct json_object *main_obj;
  struct json_object *description_obj;
  const char *description;
  double temp;

  json_obj = json_tokener_parse(chunk->memory);
  json_object_object_get_ex(json_obj, "main", &main_obj);
  json_object_object_get_ex(main_obj, "temp", &temp);
  json_object_object_get_ex(json_obj, "weather", &description_obj);
  json_object_array_get_idx(description_obj, 0, &description_obj);
  json_object_object_get_ex(description_obj, "description", &description);

  printf("Temperature: %0.2f°C\n", temp);
  printf("Description: %s\n", description);

  json_object_put(json_obj);
}

int main() {
  struct MemoryStruct chunk;

  char location[256];
  printf("Enter a location: ");
  scanf("%s", location);

  fetch_weather_data(location, &chunk);
  parse_weather_data(&chunk);

  free(chunk.memory);

  return 0;
}
