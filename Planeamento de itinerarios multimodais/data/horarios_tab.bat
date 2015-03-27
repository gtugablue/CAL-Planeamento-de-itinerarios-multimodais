@echo off

for %%x in (200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 300, 301, 302, 303, 304, 305, 400, 401, 500, 501, 502, 503, 504, 505, 506, 507, 508, 600, 601, 602, 603, 604, 700, V94, 701, 702, 703, 704, 705, 706, 707, 800, 801, 803, 804, 805, 806, 900, 901, 902, 903, 904, 905, 906, 907, 103, 104, 106, 1, 18, 22, 1M, 3M, 4M, 5M, 7M, 8M, 9M, 10M, 11M, 12M, 13M) do (
for /l %%y in (0, 1, 1) do (
	wget.exe --header="Content-Type: application/x-www-form-urlencoded; charset=UTF-8" --post-data="a=buildLineTimeTable&lcode=%%x&ldir=%%y&thor=1&tdia=1" "http://www.stcp.pt/xmlhttprequests/linhas/horarios_tab.php" -O "horarios_tab\%%x-%%y-1-1"
	)
)