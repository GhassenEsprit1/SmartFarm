#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>


#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "troupeaux.h"
char types[100];
char typeajout[100];
char typemodif[100];
troup t;





void
on_buttonajouter_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)

{

troup t;
int o=0;

GtkWidget *input1, *sexe, *input3, *type, *input5, *input6;
GtkWidget *labelider,*labeldateer,*labelrefer;
GtkWidget *ajout;


ajout=lookup_widget(objet,"ajout");

input1=lookup_widget(objet,"entryid");
sexe=lookup_widget(objet, "combobox3");
input3=lookup_widget(objet,"entrydate");
input5=lookup_widget(objet,"spinbutton1");
sprintf(t.poids,"%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5)));
input6=lookup_widget(objet,"entry_ref");

strcpy(t.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(t.date,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(t.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(sexe)));
strcpy(t.ref,gtk_entry_get_text(GTK_ENTRY(input6)));
strcpy(t.type,typeajout);
strcpy(t.poids,gtk_entry_get_text(GTK_ENTRY(input5)));

labelider=lookup_widget(ajout,"labelider");
labeldateer=lookup_widget(ajout,"labeldateer");
labelrefer=lookup_widget(ajout,"labelrefer");

if(strcmp(t.id,"")==0)
{o=1;
gtk_widget_show(labelider);
}
else
{gtk_widget_hide(labelider);
}
if(strcmp(t.date,"")==0)
{o=1;
gtk_widget_show(labeldateer);
}
else
{gtk_widget_hide(labeldateer);
}
if(strcmp(t.ref,"")==0)
{o=1;
gtk_widget_show(labelrefer);}
else
{gtk_widget_hide(labelrefer);}
if(o==0)
{ajouter(t);}
}


void
on_buttonretour_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)

{
GtkWidget *ajout;
GtkWidget *gestion;
GtkWidget *treeview1;

ajout=lookup_widget(objet,"ajout");

gtk_widget_destroy(ajout);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();

gtk_widget_show(gestion);


treeview1=lookup_widget(gestion,"treeview1");

afficher(treeview1);
}




void
on_button_calcul_activate              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_ajout_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *ajout;
GtkWidget *gestion;
GtkWidget *treeview1;

gestion=lookup_widget(objet,"gestion");
gtk_widget_destroy(gestion);
ajout=lookup_widget(objet,"ajout");
ajout=create_ajout();
gtk_widget_show(ajout);
GtkWidget *erreur_id,*erreur_date,*erreur_poids,*erreur_ref;
erreur_id=lookup_widget(ajout,"labelider");
erreur_date=lookup_widget(ajout,"labeldateer");
erreur_poids=lookup_widget(ajout,"labelpoidser");
erreur_ref=lookup_widget(ajout,"labelrefer");
gtk_widget_hide(erreur_id);
gtk_widget_hide(erreur_date);
gtk_widget_hide(erreur_poids);
gtk_widget_hide(erreur_ref);

}



void
on_button_rechercher_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
char idchercher[100];
GtkWidget *input1;
GtkWidget *gestion;
GtkWidget *windowchercher;
GtkWidget *treeview1;
input1=lookup_widget(objet,"entry8");

strcpy(idchercher,gtk_entry_get_text(GTK_ENTRY(input1)));
gestion=lookup_widget(objet,"gestion");

//gtk_widget_destroy(gestion);
//windowchercher=lookup_widget(objet,"windowchercher");
//windowchercher=create_windowchercher();

//gtk_widget_show(windowchercher);


treeview1=lookup_widget(objet,"treeview1");

chercher(idchercher, treeview1 );
}




void
on_button_modifier_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *windowmodif;
GtkWidget *gestion;

gestion=lookup_widget(objet,"gestion");
gtk_widget_destroy(gestion);
windowmodif=lookup_widget(objet,"windowmodif");
windowmodif=create_windowmodif();
gtk_widget_show(windowmodif);
troup t1;
FILE *f;
f=fopen("troupeaux.txt","r");
while(fscanf(f,"%s %s %s %s %s %s \n",t1.id,t1.date,t1.poids,t1.ref,t1.type,t1.sexe)!=EOF)
{
if (strcmp(t.id,t1.id)==0)
{
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(windowmodif,"entry3")),t1.id);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(windowmodif,"entry5")),t1.date);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(windowmodif,"entry6")),t1.poids);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(windowmodif,"entry7")),t1.id);
		
}
}
}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* id;
	gchar* date;
	gchar* poids;
	gchar* ref;
	gchar* type;
	gchar* sexe;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	GtkWidget *calcul;
	if (gtk_tree_model_get_iter(model, &iter ,path))
	{
		
		gtk_tree_model_get (GTK_LIST_STORE(model),&iter, 0, &id, 1, &date, 2, &poids ,3, &ref ,4,&type ,5, &sexe,-1);
		strcpy(t.id,id);
		strcpy(t.date,date);
		strcpy(t.poids,poids);
		strcpy(t.ref,ref);
		strcpy(t.type,type);
		strcpy(t.sexe,sexe);

	}


}

void
on_buttonmodif_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *input1, *sexe, *input3, *input4, *input5, *type;
troup t;
input1=lookup_widget(objet,"entry3");
sexe=lookup_widget(objet, "combobox4");
input3=lookup_widget(objet,"entry5");
input4=lookup_widget(objet,"spinbutton2");
sprintf(t.poids,"%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4)));
input5=lookup_widget(objet,"entry7");

strcpy(t.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(t.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(sexe)));
strcpy(t.date,gtk_entry_get_text(GTK_ENTRY(input3)));
strcpy(t.ref,gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(t.type,typemodif);

modifier(t);

}

void
on_buttonmodifretourn_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *windowmodif;
GtkWidget *gestion;
GtkWidget *treeview1;

windowmodif=lookup_widget(objet,"windowmodif");

gtk_widget_destroy(windowmodif);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();

gtk_widget_show(gestion);


treeview1=lookup_widget(gestion,"treeview1");

afficher(treeview1);
}


void
on_retour_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *windowchercher;
GtkWidget *gestion;

windowchercher=lookup_widget(objet,"windowchercher");
gtk_widget_destroy(windowchercher);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();
gtk_widget_show(gestion);
}

void
on_refresh_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *gestion;
GtkWidget *treeview1;
gestion=lookup_widget(objet,"gestion");
treeview1=lookup_widget(gestion,"treeview1");
afficher(treeview1);

}


void
on_calcul_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *calcul;
GtkWidget *gestion;
gestion=lookup_widget(objet,"gestion");
gtk_widget_destroy(gestion);
calcul=lookup_widget(objet,"calcul");
calcul=create_calcul();
gtk_widget_show(calcul);

}





void
on_button_calculer_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *label;
label=lookup_widget(objet,"labeltype");
int n;
char nu[100];
n=calcul(types);
sprintf(nu,"%d",n);
gtk_label_set_text(GTK_LABEL(label),nu);

}



void
on_button_calcul_retour_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *calcul;
GtkWidget *gestion;

calcul=lookup_widget(objet,"calcul");
gtk_widget_destroy(calcul);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();
gtk_widget_show(gestion);

}


void
on_radiobuttonbrebis_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{strcpy(types,"Brebis");}
}


void
on_radiobuttonveau_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{strcpy(types,"Veau");}


}


void
on_checkbutton_brebis_ajout_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{
strcpy(typeajout,"Brebis");
}
}


void
on_checkbutton_veau_ajout_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{
strcpy(typeajout,"Veau");
}
}


void
on_checkbutton_brebis_modif_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{
strcpy(typemodif,"Brebis");
}

}


void
on_checkbutton_veau_modif_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{
strcpy(typemodif,"Veau");
}
}


void
on_windowmodif_show                    (GtkWidget       *objet,
                                        gpointer         user_data)
{


}


void
on_button_supp_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *window_confirm;
GtkWidget *gestion;

gestion=lookup_widget(objet,"gestion");
gtk_widget_hide(gestion);
window_confirm=lookup_widget(objet,"window_confirm");
window_confirm=create_window_confirm();
gtk_widget_show(window_confirm);

}


void
on_button2_oui_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
supprimer(t);
GtkWidget *window_confirm;
GtkWidget *gestion;
window_confirm=lookup_widget(objet,"window_confirm");
gtk_widget_destroy(window_confirm);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();
gtk_widget_show(gestion);


}


void
on_button3_non_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *window_confirm;
GtkWidget *gestion;

window_confirm=lookup_widget(objet,"window_confirm");
gtk_widget_destroy(window_confirm);
gestion=lookup_widget(objet,"gestion");
gestion=create_gestion();
gtk_widget_show(gestion);


}

