include ../../config

latex-report:
	latex report
	bibtex report
	latex report
	latex report
	dvips report -o report.ps

clean:
	$(RM) *~ */*~ report.aux report.bbl report.blg report.dvi report.log \
		report.ps report.toc texput.log report/*
