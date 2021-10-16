// functions for numeric up/down
function ValidateRange(element, min, max)
{
	var value = element.value;
	var intValue = parseInt(value);
	if (intValue > max)
		element.value = max;
	if (intValue < min)
		element.value = min;	
}

function IsNumeric(e)
{	
	var iKeyCode = 0;
	iKeyCode=window.event.keyCode;
	if(iKeyCode<48 || iKeyCode>57)
	{
		window.event.keyCode=0;
	}
}

function increment(element, inc, min, max)
{
	var value = element.value;
	var intValue = parseInt(value);
	intValue = intValue + inc;
	
	element.value = intValue;
	
	ValidateRange(element, min, max);
}

// functions for toggling a row in a multi-level grid
function ToggleRow(ctl)
{
	var row = ctl.parentNode.parentNode;
	var tbl = row.parentNode;
	var crow = tbl.rows[row.rowIndex + 1];

	tbl = tbl.parentNode;


	if (crow.style.display == 'none')
	{
		crow.style.display = '';
		ctl.innerHTML = '-';
	}
	else
	{
		crow.style.display = 'none';
		ctl.innerHTML = '+';
	}
}

// functions for the flow report
function openObservation(ObservationsTable)
{
	if (!ObservationsTable)	return false;
	if (!ObservationsTable.selectedtr) return false;
	if (!ObservationsTable.selectedtr.ObservationGuid) return false;

	ObservationsTable.selectedtr.visited = "visited";
	window.navigate("ObservationGuid:" + ObservationsTable.selectedtr.ObservationGuid);
	return false;
}

function markRow(ObservationsTable)
{
	if (!event) return;
	var tr = event.srcElement;
	
	// get the containing row
	while (tr.tagName != 'TR')
		tr = tr.parentElement;
		
	// unmark the previously marked row				
	if (ObservationsTable.selectedtr)
	{
		if (ObservationsTable.selectedtr.visited == "visited")
			ObservationsTable.selectedtr.style.backgroundColor = "pink";
		else
			ObservationsTable.selectedtr.style.backgroundColor = "";
	}
	
	// mark the selected row
	ObservationsTable.selectedtr = tr;
	tr.style.backgroundColor = "#dcae2e";												

}


function setSLAWorstTransDivMaxHeight(SLAWorstTransDiv)
{
	// if the height is too short, remove the scrollbars from the
	// div.
	if (!SLAWorstTransDiv) return;
	var scrollHeight = SLAWorstTransDiv.scrollHeight;
	if (scrollHeight > 300)
	{
		SLAWorstTransDiv.className = "InfiniteWidth300HeightClass";
	}
}

function setSLATableDivMaxHeight(SLATableDiv)
{
	// if the height is too short, remove the scrollbars from the
	// div.
	if (!SLATableDiv) return;
	var scrollHeight = SLATableDiv.scrollHeight;
	if (scrollHeight > 300)
	{
		SLATableDiv.className = "InfiniteWidth300HeightClass";
	}
}

function setObservationsDivMaxHeight(ObservationsDiv)
{
	// if the height is too short, remove the scrollbars from the
	// div.
	if (!ObservationsDiv) return;
	var scrollHeight = ObservationsDiv.scrollHeight;
	if (Math.max(scrollHeight, 400) == 400)
	{
		ObservationsDiv.className = "750WidthClass";
	}
}