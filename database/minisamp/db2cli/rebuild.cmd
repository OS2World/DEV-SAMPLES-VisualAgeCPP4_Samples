echo Generating Dax classes
cppdatag /f minisamp.dax

echo Building Dept library
vacbld -noc -sev=E Dept.icc

echo Building Empl library
vacbld -noc -sev=E Empl.icc

echo Building Photo library
vacbld -noc -sev=E Photo.icc

echo Building Join library
vacbld -noc -sev=E Join.icc

echo Building arud
vacbld -noc -sev=E arud.icc

echo Building curfetch
vacbld -noc -sev=E curfetch.icc

echo Building fill
vacbld -noc -sev=E fill.icc

echo Building gifget
vacbld -noc -sev=E gifget.icc

echo Building giflist
vacbld -noc -sev=E giflist.icc

echo Building tabljoin
vacbld -noc -sev=E tabljoin.icc

echo Building udmcsql
vacbld -noc -sev=E udmcsql.icc

echo Building udmspcpo
vacbld -noc -sev=E udmspcpo.icc

echo Building udmsqlpr
vacbld -noc -sev=E udmsqlpr.icc

