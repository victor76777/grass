/* get_maps.c */
char **get_available_mapsets(int *);
const char *substitute_mapset(const char *);

/* list.c */
void list_available_mapsets(const char **, int, const char *);
void list_accessible_mapsets(const char *);
void list_avaliable_mapsets_json(const char **, int);
void list_accessible_mapsets_json();
