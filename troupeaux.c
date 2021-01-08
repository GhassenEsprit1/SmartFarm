#ifdef HAVE_CONFIG_H
#include <config.h>
#endif



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"troupeaux.h"
#include<gtk/gtk.h>

enum
{ 
	EID,
	EDATE,
	EPOIDS,
	EREF,
	ETYPE,
        ESEXE,
	COLUMNS,
};



///////////////////////////////////////////////
void ajouter(troup t)
{
FILE *f;
f = fopen("troupeaux.txt","a+");
if (f!=NULL)
{
fprintf(f,"%s %s %s %s %s %s \n",t.id,t.date,t.poids,t.ref,t.type,t.sexe);

fclose(f);
}
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void afficher(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char id[100];
	char date[100];
	char poids[100];
	char ref[100];
	char type[100];
	char sexe[100];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);

	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id",renderer,"text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("date", renderer, "text",EDATE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("poids", renderer, "text",EPOIDS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);  

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("ref", renderer, "text",EREF,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("troupeaux.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("troupeaux.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s \n",id,date,poids,ref,type,sexe)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID, id, EDATE, date, EPOIDS, poids, EREF, ref, ETYPE, type, ESEXE, sexe, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}

}




///////////////////////////////////////////////
void supprimer(troup t)
///////////////////////////////////////////////
{
troup t2;
FILE *f,*g;
	f=fopen("troupeaux.txt","r");
	g=fopen("users2.txt","w");
	if( f==NULL  || g==NULL )
		return;
	else
	{
		while(fscanf(f,"%s %s %s %s %s %s \n",t2.id,t2.date,t2.poids,t2.ref,t2.type,t2.sexe)!=EOF)
		{
			if (strcmp(t.id,t2.id)!=0 || strcmp(t.date,t2.date)!=0 || strcmp(t.poids,t2.poids)!=0 || strcmp(t.ref,t2.ref)!=0 || strcmp(t.type,t2.type)!=0 || strcmp(t.sexe,t2.sexe)!=0)
			fprintf(g,"%s %s %s %s %s %s \n",t2.id,t2.date,t2.poids,t2.ref,t2.type,t2.sexe);
		}
		fclose(f);
		fclose(g);
	
remove("troupeaux.txt");
rename("users2.txt","troupeaux.txt");
	}


}


void modifier(troup ta)
{
troup t;
int trouve=0;
FILE *f,*f1;
f=NULL;
f1=NULL;
f=fopen("troupeaux.txt","r");
f1=fopen("troupeaux3.txt","w+");
if(f!=NULL)
{while((fscanf(f,"%s %s %s %s %s %s  ",t.id,t.date,t.poids,t.ref,t.type,t.sexe)!=EOF))
{
if(strcmp(t.id,ta.id)==0)
{trouve=1;

fprintf(f1,"%s %s %s %s %s %s \n",ta.id,ta.date,ta.poids,ta.ref,ta.type,ta.sexe);
}
else
{fprintf(f1,"%s %s %s %s %s %s \n",t.id,t.date,t.poids,t.ref,t.type,t.sexe);
}
}
}

fclose(f);
fclose(f1);
remove("troupeaux.txt");
rename("troupeaux3.txt","troupeaux.txt");


}






void chercher(char *idchercher,GtkWidget *liste )
{

FILE *f6;

GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
char id[100];
char date[100];
char poids[100];
char ref[100];
char type[100];
char sexe[100];
int test=0;
store=NULL;
store=gtk_tree_view_get_model(liste) ;

if (store==NULL)
{
 renderer =gtk_cell_renderer_text_new();
 column = gtk_tree_view_column_new_with_attributes("id",renderer,"text",EID,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

 renderer =gtk_cell_renderer_text_new();
 column = gtk_tree_view_column_new_with_attributes("date",renderer,"text",EDATE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

 renderer =gtk_cell_renderer_text_new();
 column = gtk_tree_view_column_new_with_attributes("poids",renderer,"text",EPOIDS,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

 renderer =gtk_cell_renderer_text_new();
 column = gtk_tree_view_column_new_with_attributes("ref",renderer,"text",EREF,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

 renderer =gtk_cell_renderer_text_new();
 column = gtk_tree_view_column_new_with_attributes("type",renderer,"text",ETYPE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

renderer= gtk_cell_renderer_text_new ();
column= gtk_tree_view_column_new_with_attributes("sexe",renderer,"text",ESEXE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste) , column);

}

 store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f6=fopen("troupeaux.txt","r");
if(f6==NULL)
	{
		return;
	}
else
{
f6=fopen("troupeaux.txt","a+");
while((fscanf(f6,"%s %s %s %s %s %s",id,date,poids,ref,type,sexe)!=EOF)&&(test==0))
{
if (strcmp(id,idchercher)==0)
{
test=1;
gtk_list_store_append (store,&iter);
gtk_list_store_set (store, &iter,EID,id,EDATE,date,EPOIDS,poids,EREF,ref,ETYPE,type,ESEXE,sexe, -1);
   }
   }
 fclose(f6);
 gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
 gtk_object_unref (store);
 }
}


int calcul(char *types)
{
FILE *f;
troup t;
int n=0;
f=NULL;
f=fopen("troupeaux.txt","r+");
if(f==NULL)
{return 0;}
else
{
while(fscanf(f,"%s %s %s %s %s %s \n",t.id,t.date,t.poids,t.ref,t.type,t.sexe)!=EOF)
{if(strcmp(types,t.type)==0)
{n++;}
}
}
fclose(f);
return n;
}
