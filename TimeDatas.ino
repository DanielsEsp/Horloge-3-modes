
//____________________________________________________________________________ 

void localTime() {
  
     struct tm timeinfo;
     if(!getLocalTime(&timeinfo)){
        return;
       }

     char timeHour[3];
     strftime(timeHour,3, "%H", &timeinfo);
     String heures = timeHour;
     DFheures = heures.toInt();
     int dizHeure = heures.substring(0, 1).toInt();
     int uniHeure = heures.substring(1, 2).toInt();          

     char timeMinute[3];
     strftime(timeMinute,3, "%M", &timeinfo);
     String minutes = timeMinute;
     DFminutes = minutes.toInt();
     int dizMinute = minutes.substring(0, 1).toInt();
     int uniMinute = minutes.substring(1, 2).toInt();

     char timeInfoDay[2];
     strftime(timeInfoDay,2, "%u", &timeinfo);    
     int timeDay = String(timeInfoDay).toInt();     
     DFjour = timeDay;
     char timeInfoJour[3];
     strftime(timeInfoJour,3, "%e", &timeinfo);    
     int timeJour = String(timeInfoJour).toInt();    
     DFdate = timeJour;
     char timeInfoMois[3];
     strftime(timeInfoMois,3, "%m", &timeinfo);     
     int timeMois = String(timeInfoMois).toInt();     
     DFmois = timeMois;
    
     hh = String(timeHour).toInt();
     mm = String(timeMinute).toInt();
     
}
