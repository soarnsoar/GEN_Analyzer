cp JHanalyzer_muon.cc JHanalyzer_electron.cc


#leppid=11
find . -name "JHanalyzer_electron.cc" | xargs perl -pi -e s/"leppid=13"/"leppid=11"/g
find . -name "JHanalyzer_electron.cc" | xargs perl -pi -e s/"JHanalyzer_muon"/"JHanalyzer_electron"/g