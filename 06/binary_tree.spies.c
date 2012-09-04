#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *question;
  struct node *no;
  struct node *yes;
} node;

int yes_no(char *question)
{
  char answer[3];
  printf("%s? (y/n): ", question);
  fgets(answer, 3, stdin);
  return answer[0] == 'y';
}

node* create(char *question)
{
  node *n = malloc(sizeof(node));
  n->question = strdup(question);
  n->no = NULL;
  n->yes = NULL;
  return n;
}

void replace_question(node *n, char *question)
{
  /* This free() fixes a memory leak! */
  free(n->question);
  /* *
   * p. 308
   * "The 'Loretta' data was put on the heap on line 46 (now 61), but the
   * leak happened when the variable pointing to it ('current->question')
   * was reassigned without freeing it.
   * Leaks don't happen when data is created, they happen when 
   * the program loses all references to the data."
   * */
  n->question = strdup(question);
}

void release(node *n)
{
  if (n)  {
    if (n->no)
      release(n->no);
    if (n->yes)
      release(n->yes);
    if (n->question)
      free(n->question);

    free(n);
  }
}
int main()
{
  char question[80];
  char suspect[20];
  node *start_node = create("Does suspect have a mustache");
  start_node->no   = create("Loretta Barnsworthy");
  start_node->yes  = create("Vinny the Spoon");

  node *current;
  do {
    current = start_node;
    while(1)  {
      if (yes_no(current->question))
      {
        if (current->yes) {
          current = current->yes;
        } else {
          puts("SUSPECT IDENTIFIED");
          break;
        }
      } else if (current->no) {
        current = current->no;
      } else {
        /* Make the yes-node the new suspect name */
        printf("Who's the suspect? ");
        fgets(suspect, 20, stdin);
        current->yes = create(suspect);

        /* Make the no-node a copy of this question */
        current->no = create(question);

        /* Then replace this question with the new question */
        printf("Give me a question that is TRUE for %s but not for %s: ", suspect,
            current->question);
        fgets(question, 80, stdin);

        replace_question(current, question);

        break;
      }
    }
  } while(yes_no("Run again"));
  release(start_node);
  return 0;
}
