cp JHanalyzer_muon_status2223.cc JHanalyzer_electron_status2223.cc


#leppid=11
find . -name "JHanalyzer_electron_status2223.cc" | xargs perl -pi -e s/"leppid=13"/"leppid=11"/g
find . -name "JHanalyzer_electron_status2223.cc" | xargs perl -pi -e s/"JHanalyzer_muon"/"JHanalyzer_electron"/g