/*------------------------------------------------------------------------------
    List (LIST) Library Implementation in Assembly Language with C Interface
    Copyright (C) 2025  J. McIntosh

    LIST is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    LIST is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with LIST; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
------------------------------------------------------------------------------*/
#include "main.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main (int argc, char *argv[])
{
  data_list_test();

  pair_list_test();

  return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_assign_boolean (data_t *data, char const *value)
{
  data->type = TYPE_BOOLEAN;
  data->value.str = (char *)value;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_assign_double (data_t *data, double value)
{
  data->type = TYPE_DOUBLE;
  data->value.dbl = value;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_assign_long (data_t *data, long value)
{
  data->type = TYPE_LONG;
  data->value.lng = value;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_assign_string (data_t *data, char const *value)
{
  data->type = TYPE_STRING;
  data->value.str = strdup(value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_list_term (list_t *list)
{
  for (data_t *data = list_begin(list);
      data != NULL;
      data = list_next(list))
  {
    data_term(data);
  }
  list_term(list);
  list_free(list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_list_test (void)
{
  list_t *list;
  if ((list = list_alloc()) == NULL) return;

  if (list_init(list, sizeof(data_t)) < 0) return;

  data_t data;
  data_assign_long(&data, -128);
  if (list_add(list, &data) < 0) return;

  data_assign_double(&data, DBL_MAX);
  if (list_add(list, &data) < 0) return;

  data_assign_boolean(&data, TRUE);
  if (list_add(list, &data) < 0) return;

  data_assign_string(&data, "THIS IS A STRING");
  if (list_add(list, &data) < 0) return;

  data_assign_double(&data, -0.0009876);
  if (list_add(list, &data) < 0) return;

  data_assign_string(&data, "THIS TOO IS A STRING");
  if (list_add(list, &data) < 0) return;

  data_assign_boolean(&data, FALSE);
  if (list_add(list, &data) < 0) return;

  data_assign_long(&data, (1024 * 1024));
  if (list_add(list, &data) < 0) return;

  data_assign_double(&data, 0.987000321);
  if (list_add(list, &data) < 0) return;

  data_assign_boolean(&data, FALSE);
  if (list_add(list, &data) < 0) return;

  data_assign_string(&data, "THIS IS ALSO A STRING");
  if (list_add(list, &data) < 0) return;

  data_assign_double(&data, -0.1234067);
  if (list_add(list, &data) < 0) return;

  data_assign_string(&data, "YET ANOTHER STRING");
  if (list_add(list, &data) < 0) return;

  data_assign_long(&data, (1024 * 1024 * 10));
  if (list_add(list, &data) < 0) return;

  data_assign_boolean(&data, TRUE);
  if (list_add(list, &data) < 0) return;

  data_assign_double(&data, 0.010203);
  if (list_add(list, &data) < 0) return;

  data_assign_string(&data, "AND ONE MORE STRING");
  if (list_add(list, &data) < 0) return;

  data_assign_long(&data, (2048 * 10));
  if (list_add(list, &data) < 0) return;

  data_assign_boolean(&data, FALSE);
  if (list_add(list, &data) < 0) return;

  print_data_list(list);

  data_list_term (list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void data_term (data_t *data)
{
  if (data->type == TYPE_STRING) free(data->value.str);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_assign_boolean (pair_t *pair, char const *key, char const *value)
{
  pair->key = strdup(key);
  data_assign_boolean(&pair->data, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_assign_double (pair_t *pair, char const *key, double value)
{
  pair->key = strdup(key);
  data_assign_double(&pair->data, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_assign_long (pair_t *pair, char const *key, long value)
{
  pair->key = strdup(key);
  data_assign_long(&pair->data, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_assign_string (pair_t *pair, char const *key, char const *value)
{
  pair->key = strdup(key);
  data_assign_string(&pair->data, value);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_list_term (list_t *list)
{
  for (pair_t *pair = list_begin(list);
      pair != NULL;
      pair = list_next(list))
  {
    pair_term(pair);
  }
  list_term(list);
  list_free(list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_list_test (void)
{
  list_t *list;
  if ((list = list_alloc()) == NULL) return;

  if (list_init(list, sizeof(pair_t)) < 0) return;

  pair_t pair;
  pair_assign_long(&pair, "LONG_01", -128);
  if (list_add(list, &pair) < 0) return;

  pair_assign_double(&pair, "DOUBLE_01", DBL_MAX);
  if (list_add(list, &pair) < 0) return;

  pair_assign_boolean(&pair, "BOOLEAN_01", TRUE);
  if (list_add(list, &pair) < 0) return;

  pair_assign_string(&pair, "STRING_01", "THIS IS A STRING");
  if (list_add(list, &pair) < 0) return;

  pair_assign_double(&pair, "DOUBLE_02", -0.0009876);
  if (list_add(list, &pair) < 0) return;

  pair_assign_string(&pair, "STRING_02", "THIS TOO IS A STRING");
  if (list_add(list, &pair) < 0) return;

  pair_assign_boolean(&pair, "BOOLEAN_02", FALSE);
  if (list_add(list, &pair) < 0) return;

  pair_assign_long(&pair, "LONG_02", (1024 * 1024));
  if (list_add(list, &pair) < 0) return;

  pair_assign_double(&pair, "DOUBLE_03", 0.987000321);
  if (list_add(list, &pair) < 0) return;

  pair_assign_boolean(&pair, "BOOLEAN_03", FALSE);
  if (list_add(list, &pair) < 0) return;

  pair_assign_string(&pair, "STRING_03", "THIS IS ALSO A STRING");
  if (list_add(list, &pair) < 0) return;

  pair_assign_double(&pair, "DOUBLE_04", -0.1234067);
  if (list_add(list, &pair) < 0) return;

  pair_assign_string(&pair, "STRING_04", "YET ANOTHER STRING");
  if (list_add(list, &pair) < 0) return;

  pair_assign_long(&pair, "LONG_03", (1024 * 1024 * 10));
  if (list_add(list, &pair) < 0) return;

  pair_assign_boolean(&pair, "BOOLEAN_04", TRUE);
  if (list_add(list, &pair) < 0) return;

  pair_assign_double(&pair, "DOUBLE_05", 0.010203);
  if (list_add(list, &pair) < 0) return;

  pair_assign_string(&pair, "STRING_05", "AND ONE MORE STRING");
  if (list_add(list, &pair) < 0) return;

  pair_assign_long(&pair, "LONG_04", (2048 * 10));
  if (list_add(list, &pair) < 0) return;

  pair_assign_boolean(&pair, "BOOLEAN_05", FALSE);
  if (list_add(list, &pair) < 0) return;

  print_pair_list(list);

  pair_list_term(list);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void pair_term (pair_t *pair)
{
  free(pair->key);
  data_term(&pair->data);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void print_data (data_t *data)
{
  switch (data->type)
  {
    case TYPE_DOUBLE:
      printf("%g\n", data->value.dbl);
      break;
    case TYPE_LONG:
      printf("%ld\n", data->value.lng);
      break;
    case TYPE_STRING:
      printf("\"%s\"\n", data->value.str);
      break;
    case TYPE_BOOLEAN:
      printf("%s\n", data->value.str);
      break;
    default:;
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void print_data_list (list_t *list)
{
  printf("\nDATA LIST:\n----------\n");
  for (data_t *data = list_begin(list);
      data != NULL;
      data = list_next(list))
  {
    print_data(data);
  }
  putchar('\n');
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void print_pair (pair_t *pair)
{
  printf("\"%s\":\t", pair->key);
  print_data(&pair->data);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void print_pair_list (list_t *list)
{
  printf("PAIR LIST:\n----------\n");
  for (pair_t *pair = list_begin(list);
      pair != NULL;
      pair = list_next(list))
  {
    print_pair(pair);
  }
  putchar('\n');
}

