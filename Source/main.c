/* Show the CGI (Common Gateway Interface) environment variables */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Print a basic HTTP header. */

static void 
print_http_header (const char * content_type)
{
    printf ("Content-Type: %s\n\n", content_type);
    printf("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css' integrity='sha384-JcKb8q3iqJ61gNV9KGb8thSsNjpSL0n8PARn9HuZOnIxN0hoP+VmmDGMN5t9UJ0Z' crossorigin='anonymous'>");
}

void 
print_file(FILE *f){
    int c;
    if (f){
        while((c = getc(f)) != EOF)
            putchar(c);
        fclose(f);
    }
}
 
int 
main (){
    print_http_header ("text/html");

    FILE* table = fopen("/usr/lib/cgi-bin/Source/page.html", "r");
    print_file(table);

    char *content = getenv("CONTENT_LENGTH");


    if(content) {
        int ln = atoi(content);
        char postdata[ln +1];

       time_t  tijd = time(NULL);
       char * tijdstr =  ctime(&tijd);
       tijdstr[strlen(tijdstr) -1] = '\0';

        fgets(postdata, sizeof(postdata), stdin);
        //printf("<p>%s</p>", postdata); print de postdata op de webpagina
        char *ptr = strtok(postdata,"&=");
        
        ptr = strtok(NULL, "&=");
        char * data = ptr;
        //printf("<p>%s</p>", ptr); print eerste data waarde op webpagina
        ptr = strtok(NULL, "&=");
        ptr = strtok(NULL, "&=");
        char * data2 = ptr;
        //printf("<p>%s</p>", ptr); print eerste data waarde op webpagina
        ptr = strtok(NULL, "&=");
        ptr = strtok(NULL, "&=");
        char * data3 = ptr;
        //printf("<p>%s</p>", ptr); print eerste data waarde op webpagina

        system("truncate -s-1 /var/www/html/data.json");
        FILE* filejson = fopen("/var/www/html/data.json", "a");
        fprintf(filejson, ",{\"koekje\": \"%s\",\"merk\": \"%s\",\"rating\": \"%s\",\"time\": \"%s\"}]",data,data2,data3,tijdstr);
    }
    return 0;
}