#include <stdio.h>
#include <stdlib.h>
#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include <string.h>
#include "libfdr/jval.h"

int main(int argc, char **argv)
{
  
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) 
  {
    (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
  }

  jrb_traverse(bn, b) 
  {
    printf("%s", bn->key.s);
  }

  return 0;
}
