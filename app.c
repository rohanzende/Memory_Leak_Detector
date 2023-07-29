#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

/*Application Structures*/


typedef struct book_ {
    char book_name[30];
    unsigned int book_id;
    struct student_ * has_taken_by;
    struct book_ * refe;
}book_t;

typedef struct student_{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleage;
    struct book_ *has_taken;
} student_t;

int
main(int argc, char **argv){

    /*Step 1 : Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    mld_init_primitive_data_types_support(struct_db);

    /*Step 2 : Create structure record for structure emp_t*/
    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t),
        FIELD_INFO(student_t, has_taken, OBJ_PTR, book_t)
    };
    /*Step 3 : Register the structure in structure database*/
    REG_STRUCT(struct_db, student_t, stud_fiels);

     static field_info_t book_fiels[] = {
        FIELD_INFO(book_t, book_name, CHAR, 0),
        FIELD_INFO(book_t, book_id,    UINT32, 0),
        FIELD_INFO(book_t, has_taken_by , OBJ_PTR, student_t),
        FIELD_INFO(book_t, refe , OBJ_PTR, book_t)
    };
    REG_STRUCT(struct_db, book_t, book_fiels);

    /*Step 4 : Verify the correctness of structure database*/
    print_structure_db(struct_db);



    /*Working with object database*/
    /*Step 1 : Initialize a new Object database */
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;

    /*Step 2 : Create some sample objects, equivalent to standard
     * calloc(1, sizeof(student_t))*/
    student_t * rohan = xcalloc(object_db, "student_t", 1);
    strncpy(rohan->stud_name, "rohan", strlen("rohan"));
    mld_set_dynamic_object_as_root(object_db, rohan);

    student_t * shivani= xcalloc(object_db, "student_t", 1);
    strncpy(shivani->stud_name, "shivani", strlen("shivani"));

     student_t * sagar= xcalloc(object_db, "student_t", 1);
    strncpy(sagar->stud_name, "sagar", strlen("sagar"));

     student_t * yash = xcalloc(object_db, "student_t", 1);
    strncpy(yash->stud_name, "yash", strlen("yash"));

    student_t * akshay= xcalloc(object_db, "student_t", 1);
    strncpy(akshay ->stud_name, "akshay", strlen("akshay"));

    student_t * radhe = xcalloc(object_db, "student_t", 1);
    strncpy(radhe->stud_name, "radhe", strlen("radhe"));

    student_t *yuvraj = xcalloc(object_db, "student_t", 1);
    strncpy(yuvraj->stud_name, "yuvraj", strlen("yuvraj"));
    mld_set_dynamic_object_as_root(object_db, yuvraj);

    student_t *akash = xcalloc(object_db, "student_t", 1);
    strncpy(akash->stud_name, "akash", strlen("akash"));

    student_t *suraj = xcalloc(object_db, "student_t", 1);
    strncpy(suraj->stud_name, "suraj", strlen("suraj"));

    book_t * ode = xcalloc(object_db, "book_t", 1);
    strncpy(ode->book_name, "ode", strlen("ode"));

    book_t *mvc = xcalloc(object_db, "book_t", 1);
    strncpy(mvc->book_name, "mvc", strlen("mvc"));

    book_t *history = xcalloc(object_db, "book_t", 1);
    strncpy(history->book_name, "history", strlen("history"));

    book_t *civics = xcalloc(object_db, "book_t", 1);
    strncpy(civics->book_name, "civics", strlen("civics"));

    book_t *clpd= xcalloc(object_db, "book_t", 1);
    strncpy(clpd->book_name, "clpd", strlen("clpd"));

    book_t *digi = xcalloc(object_db, "book_t", 1);
    strncpy(digi->book_name, "digi", strlen("digi"));

     rohan->best_colleage = shivani;
     shivani->best_colleage = sagar;
     sagar->best_colleage = yash;
     akshay->best_colleage = yash;
     radhe->best_colleage = yash;
     radhe->best_colleage = akshay;
     akash->best_colleage = sagar;
     yuvraj->best_colleage = sagar;
     yuvraj->best_colleage=suraj;
     shivani->has_taken=ode;
     ode->refe=mvc;
     mvc->has_taken_by=sagar;
     mvc->has_taken_by=radhe;
     suraj->has_taken=clpd;
     clpd->refe=digi;
     digi->has_taken_by=yuvraj;
     history->refe=civics;
     civics->has_taken_by=suraj;
     history->has_taken_by=suraj;







    print_object_db(object_db);


    run_mld_algorithm(object_db);
    printf("Leaked Objects : \n");
    report_leaked_objects(object_db);

    return 0;
}
