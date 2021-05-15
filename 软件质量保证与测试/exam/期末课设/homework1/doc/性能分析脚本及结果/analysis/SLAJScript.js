function CheckElementExistence(name)
{
	if(!document.getElementById(name))
		return false;
	else
		return true;
}



function InvokeFlowForProblematicSection(WorstTxTable)
{
	if (!WorstTxTable)	return false;
	if (!WorstTxTable.selectedtr) return false;
	
	var txName = WorstTxTable.selectedtr.txName;
	var startTime = WorstTxTable.selectedtr.startTime;
	var endTime = WorstTxTable.selectedtr.endTime;

	window.navigate("sla_invoke_analyze_tx:valid:" + String(txName) + ":" + String(startTime) + ":" + String(endTime));
	return false;
}


function init_SLAData(tableName)
{
	var SLAData = new Object();
	
	SLAData.startingCellIndex = 0;
	SLAData.endingCellIndex = 0;
	SLAData.selectionStartTime = 0;
	SLAData.selectionEndTime = 0;
	SLAData.keyDown = false;
	SLAData.msrName = "";
	SLAData.tblName = tableName;
	
	SLAData.originalPassColor = '66CC33';
	SLAData.originalFailColor = 'FF3300';
	SLAData.originalNoDataColor = 'CCCCCC';
	
	return SLAData;
}


function init_SLACtrls(txList, startTimeH, startTimeM, startTimeS, endTimeH, endTimeM, endTimeS, startTimeLimit, endTimeLimit)
{
	var SLACtrls = new Object();	
	
	SLACtrls.txList = txList;
	/*
	SLACtrls.startTimeEdit = startTimeEdit;
	SLACtrls.endTimeEdit = endTimeEdit;
	*/

	
	SLACtrls.startTimeH = startTimeH;
	SLACtrls.startTimeM = startTimeM;
	SLACtrls.startTimeS = startTimeS;		
	
	SLACtrls.endTimeH = endTimeH;
	SLACtrls.endTimeM = endTimeM;
	SLACtrls.endTimeS = endTimeS;		
	

	SLACtrls.StartTimeLimitInSec = parseInt(startTimeLimit);
	SLACtrls.EndTimeLimitInSec = parseInt(endTimeLimit);	 
	
	return SLACtrls;
}


function InitializeSLACtrls(SLAData, SLACtrls, txName, startTimeH, startTimeM, startTimeS, endTimeH, endTimeM, endTimeS)
{
	for(i=0;i<SLACtrls.txList.options.length;i++)
	{
		if(SLACtrls.txList.options[i].innerHTML == txName)
		{
			SLACtrls.txList.selectedIndex = i;
			document.getElementById("tx_list")[document.getElementById("tx_list").selectedIndex].selected=true;
		}
	}


	SLACtrls.startTimeH.value = String(startTimeH);
	PaddCtrl(SLACtrls.startTimeH);
	

	SLACtrls.startTimeM.value = String(startTimeM);
	PaddCtrl(SLACtrls.startTimeM);

	SLACtrls.startTimeS.value = String(startTimeS);
	PaddCtrl(SLACtrls.startTimeS);

	SLACtrls.endTimeH.value = String(endTimeH);
	PaddCtrl(SLACtrls.endTimeH);

	SLACtrls.endTimeM.value = String(endTimeM);
	PaddCtrl(SLACtrls.endTimeM);

	SLACtrls.endTimeS.value = String(endTimeS);
	PaddCtrl(SLACtrls.endTimeS);

	MarkCells(SLAData, SLACtrls)
}


// **** Mark the Grid and update the controls ****
// ***********************************************
function grid_mousedown(SLAData, SLACtrls)
{	
	var currentTDElement;
	
	ResetGrid(SLAData, document.getElementById(SLAData.tblName));

	currentTDElement = this.event.srcElement;
	while(currentTDElement.tagName.toLowerCase() != "td")
	{
		currentTDElement = currentTDElement.parentNode;
	}

	SLAData.startingCellIndex = parseInt(currentTDElement.index);
	SLAData.endingCellIndex = parseInt(currentTDElement.index);
	
	SetBorderStyle(currentTDElement);
	
	//currentTDElement.setAttribute("bgcolor", "Blue", 0);
	SLAData.keyDown = true;
	
	
	SLAData.msrName = currentTDElement.parentNode.id;		
	
	SLAData.selectionStartTime = currentTDElement.StartTime;		
	SLAData.selectionEndTime = currentTDElement.EndTime;
	
			
	/*		
	UpdateStartTimeBox(selectionStartTime);
	UpdateEndTimeBox(selectionEndTime);
	*/
	
	/*		
	document.getElementById("mydiv").innerText = keyDown;
	*/
	
	UpdateSLACtrlsBySLAData(SLAData, SLACtrls);
			
	return true;
}
		
		
				
function grid_mouseover(SLAData)
{
	var currentTDElement;
	
	this.event.srcElement.focus();
		
	if(SLAData.keyDown == true)
	{
		ResetGrid(SLAData, document.getElementById(SLAData.tblName));
	
		currentTDElement = this.event.srcElement;
		while(currentTDElement.tagName.toLowerCase() != "td")
		{
			currentTDElement = currentTDElement.parentNode;
		}
		
		 
		var vectorElement = currentTDElement.parentNode;
		var cells = vectorElement.cells;				

		var destCellIndex = parseInt(currentTDElement.index);
		var endingCellObject = currentTDElement;
				
		var currentCell;
		var currentCellIndex;
		var startingCellObject;
		var i;
				
		for(i=0;i < cells.length;i++)
		{
			currentCell = cells[i];
			currentCellIndex = parseInt(currentCell.index);

			if(currentCellIndex == SLAData.startingCellIndex)
				startingCellObject = currentCell; 

			if(endingCellObject == currentCell)
				SLAData.endingCellIndex = currentCellIndex;

			if( ((currentCellIndex <= destCellIndex) && (currentCellIndex >= SLAData.startingCellIndex)) ||
				((currentCellIndex >= destCellIndex) && (currentCellIndex <= SLAData.startingCellIndex)) )
				//currentCell.bgColor = "blue";
			{
				SetBorderStyle(currentCell);
			}
		}
				
				
		if(SLAData.endingCellIndex >= SLAData.startingCellIndex)
		{
			SLAData.selectionEndTime = endingCellObject.EndTime;
			SLAData.selectionStartTime = startingCellObject.StartTime;
		}
		else
		{
			SLAData.selectionEndTime = startingCellObject.EndTime;
			SLAData.selectionStartTime = endingCellObject.StartTime;
		}


		SLAData.msrName = currentTDElement.parentNode.id;

		/*
		UpdateStartTimeBox(selectionStartTime);
		UpdateEndTimeBox(selectionEndTime);
		*/
		
		UpdateSLACtrlsBySLAData(SLAData, SLACtrls);
	}
		
	return true;
}
		
		
function grid_onmouseup(SLAData)
{
	SLAData.keyDown = false;
	//document.getElementById("mydiv").innerText = keyDown;
	return true;
}
		
				 
function grid_onmouseleave(SLAData)
{
	SLAData.keyDown = false;
	//keyDown = false;
	//document.getElementById("mydiv").innerText = keyDown;
	return true;
}
				
				
/*		
function UpdateStartTimeBox(selectionStartTime)
{
	var startTimeBox = document.getElementById("start_time");
	startTimeBox.value = selectionStartTime;
}
		
		
function UpdateEndTimeBox(selectionEndTime)
{
	var endTimeBox = document.getElementById("end_time");
	endTimeBox.value = selectionEndTime;
}
*/		

/*		
function doclick_reset(SLAData)
{
	ResetGrid(SLAData, document.getElementById(SLAData.tblName));
}
*/		
		
function ResetGrid(SLAData, tbl)
{
	var vectorElement;
	var cells;
	var i,j;
	var status;
	
	for(i=0;i<tbl.rows.length;i++)
	{
		vectorElement = tbl.rows[i];
		
		if(vectorElement.cells.length != 2)
			continue;
		
		internalBucketsCell = vectorElement.cells[1];
		SLAsCell = internalBucketsCell.firstChild;
		
		if(!SLAsCell) 
			continue;
			
		if(SLAsCell.tagName.toLowerCase() != "table")
			continue;
		
		if(!SLAsCell.rows[0].id)
			continue;
		
		cells = SLAsCell.rows[0].cells;
				
		for(j=0;j<cells.length;j++)
		{
			/*
			status = cells[j].getAttribute("status");
			if(status == "pass")
				cells[j].bgColor = SLAData.originalPassColor;
	
			if(status == "fail")
				cells[j].bgColor = SLAData.originalFailColor;
				
			if(status == "nodata")
				cells[j].bgColor = SLAData.originalNoDataColor;
			*/
			
			ClearBorderStyle(cells[j]);	
		}
			
		/*
		UpdateStartTimeBox("");
		UpdateEndTimeBox("");
		*/
		
		//SLAData.msrName = "";
		//UpdateSLACtrlsBySLAData(SLAData, SLACtrls);
	}
}
		
		
function general_mouseup()
{
	SLAData.keyDown = false;
	//document.getElementById("mydiv").innerText = keyDown;
	return true;
}
		
	
/*	
function doclick_zoomin()
{
	var startTime = document.getElementById("start_time").value;
	var endTime = document.getElementById("end_time").value;
	var url = "SLADrillDown:tx5:"+startTime+":"+endTime;
	window.navigate(url);	
}
*/


function UpdateSLACtrlsBySLAData(SLAData, SLACtrls)
{
	/*
	SLACtrls.startTimeEdit.value = SecToTimeStr(SLAData.selectionStartTime);
	SLACtrls.endTimeEdit.value = SecToTimeStr(SLAData.selectionEndTime);
	*/
	
	SLACtrls.startTimeH.value = SecsTimeToHrsStr(SLAData.selectionStartTime);
	SLACtrls.startTimeM.value = SecsTimeToMinsStr(SLAData.selectionStartTime);
	SLACtrls.startTimeS.value = SecsTimeToSecsStr(SLAData.selectionStartTime);
	
	SLACtrls.endTimeH.value = SecsTimeToHrsStr(SLAData.selectionEndTime);
	SLACtrls.endTimeM.value = SecsTimeToMinsStr(SLAData.selectionEndTime);
	SLACtrls.endTimeS.value = SecsTimeToSecsStr(SLAData.selectionEndTime);
	
	
	for(i=0;i<SLACtrls.txList.options.length;i++)
	{
		if(SLACtrls.txList.options[i].innerHTML == SLAData.msrName)
		{
			SLACtrls.txList.selectedIndex = i;
			document.getElementById("tx_list")[document.getElementById("tx_list").selectedIndex].selected=true;
		}
	}
}

/*
function SecToTimeStr(numSecs)
{
	
	var hrs = parseInt(numSecs/3600);
	var mins = parseInt((numSecs - (hrs*3600))/60);
	var secs = numSecs - (hrs*3600) - (mins*60);
	
	var hrsStr;
	var minsStr;
	var secsStr;
	
	if(hrs < 10)
		hrsStr = "0" + String(hrs);
	else
		hrsStr = String(hrs);		

	if(mins < 10)
		minsStr = "0" + String(mins);		
	else
		minsStr = String(mins);		
	
	if(secs < 10)
		secsStr = "0" + String(secs);		
	else
		secsStr = String(secs);		
	
	var timeStr = hrsStr+':'+minsStr+":"+secsStr;
	
	return timeStr;
}
*/


function SecsTimeToSecsStr(numSecs) 
{
	var hrs = parseInt(numSecs/3600);
	var mins = parseInt((numSecs - (hrs*3600))/60);
	var secs = numSecs - (hrs*3600) - (mins*60);
	
	if(secs < 10)
		return ("0"+String(secs))
		
	return String(secs);
}


function SecsTimeToMinsStr(numSecs)
{
	var hrs = parseInt(numSecs/3600);
	var mins = parseInt((numSecs - (hrs*3600))/60);
	var secs = numSecs - (hrs*3600) - (mins*60);
	
	if(mins < 10)
		return ("0"+String(mins));
	
	return String(mins);
}


function SecsTimeToHrsStr(numSecs)
{
	var hrs = parseInt(numSecs/3600);
	var mins = parseInt((numSecs - (hrs*3600))/60);
	var secs = numSecs - (hrs*3600) - (mins*60);
	
	if(hrs < 10)
		return ("00"+String(hrs));
	
	if(hrs < 100)
		return ("0"+String(hrs));
	
	
	return String(hrs);
}


// ************************************************


// **** Update the grid according to the controls ****
// ***************************************************

function Ctrl_Change(SLAData, SLACtrls)
{
	PaddCtrl(this.event.srcElement);
	
	if(ValidateCtrls(SLACtrls) == 0)
	{
		MarkCells(SLAData, SLACtrls);
	}
	else
	{
		ResetGrid(SLAData, document.getElementById(SLAData.tblName));
	}

	return true;
}


function PaddCtrl(obj)
{
	//padding with zeros if needed
	// start time control
	if(JSTrim(obj.value) == "")	
		PaddSingleCtrl(obj, obj.maxlength)
	
	if(obj.value.length < parseInt(obj.maxLength)) 
		PaddSingleCtrl(obj, parseInt(obj.maxLength) - obj.value.length);
}


function PaddSingleCtrl(obj, numPaddDigits)
{
	var i;
	
	for(i=0;i<numPaddDigits;i++)
	{
		obj.value = "0" + obj.value;
	}
}


function ValidateCtrls(SLACtrls)
{
	// validate time ctrls against each other(start vs end).
	var startTimeInSec = TimeStrToSec(SLACtrls.startTimeH.value + ":" + SLACtrls.startTimeM.value + ":" + SLACtrls.startTimeS.value);
	var endTimeInSec = TimeStrToSec(SLACtrls.endTimeH.value + ":" + SLACtrls.endTimeM.value + ":" + SLACtrls.endTimeS.value);	
	
	if(endTimeInSec < startTimeInSec)
	{
		return 1;
	}
		
	// validate both start and end time against the edges
	if( (startTimeInSec < SLACtrls.StartTimeLimitInSec) || 
		(startTimeInSec > SLACtrls.EndTimeLimitInSec) )
	{
		return 2;
	}	
		
	if(	(endTimeInSec < SLACtrls.StartTimeLimitInSec) ||
		(endTimeInSec > SLACtrls.EndTimeLimitInSec) )
	{
		return 3;
	}
	
	
	return 0;
}



function MarkCells(SLAData, SLACtrls)
{
	// Update the SLAData object
	ResetGrid(SLAData, document.getElementById(SLAData.tblName));
	
	UpdateSLADataBySLACtrls(SLAData, SLACtrls);
		
	var msrRow = document.getElementById(SLAData.msrName);
	
	if (msrRow == null)
	  return;
	  
	var cells = msrRow.cells;
	for(i=0;i<cells.length;i++)
	{
		if( ( (cells[i].StartTime <= SLAData.selectionStartTime) && (SLAData.selectionStartTime < cells[i].EndTime) ) ||
			( (cells[i].StartTime < SLAData.selectionEndTime) && (SLAData.selectionEndTime <= cells[i].EndTime) )  ||
			( (cells[i].StartTime > SLAData.selectionStartTime) && (SLAData.selectionEndTime > cells[i].EndTime) ) )
		{
			//cells[i].bgColor = "blue";
			SetBorderStyle(cells[i]);
		}
	}
}


function UpdateSLADataBySLACtrls(SLAData, SLACtrls)
{
	var startHrsInSec = HrsStrToSec(SLACtrls.startTimeH.value);
	var startMinsInSec = MinsStrToSec(SLACtrls.startTimeM.value);
	var startSecsInSec = SecsStrToSec(SLACtrls.startTimeS.value);
	SLAData.selectionStartTime = startHrsInSec + startMinsInSec + startSecsInSec;
	
	var endHrsInSec = HrsStrToSec(SLACtrls.endTimeH.value);
	var endMinsInSec = MinsStrToSec(SLACtrls.endTimeM.value);
	var endSecsInSec = SecsStrToSec(SLACtrls.endTimeS.value);
	SLAData.selectionEndTime = endHrsInSec + endMinsInSec + endSecsInSec;
	
	SLAData.msrName = document.getElementById("tx_list")[document.getElementById("tx_list").selectedIndex].text;
}


function HrsStrToSec(hrsStr)
{
	var hrs = parseInt(hrsStr,10);	
	
	return (hrs*3600);
}


function MinsStrToSec(minsStr)
{
	var mins = parseInt(minsStr,10);	
	
	return (mins*60);
}


function SecsStrToSec(secsStr)
{
	var secs = parseInt(secsStr,10);
	
	return secs;
}


function TimeStrToSec(timeStr)
{
	var timeArr = timeStr.split(':');
	var hrs = parseInt(timeArr[0],10);
	var mins = parseInt(timeArr[1],10);
	var secs = parseInt(timeArr[2],10);
	
	// convert the time to seconds
	var timeInSecs = (hrs*3600) + (mins*60) + secs;		
	
	return timeInSecs;
}


// ***************************************************


function SetBorderStyle(element)
{
	element.style.borderStyle = "solid";
	element.style.borderWidth = 2;
	element.style.borderColor = "Blue";	
}


function ClearBorderStyle(element)
{
	element.style.borderStyle="none";
}



function ActivateAnalyze(SLACtrls)
{
	var resStr;

	var validityCode = ValidateCtrls(SLACtrls);
	var startTimeInSec = TimeStrToSec(SLACtrls.startTimeH.value + ":" + SLACtrls.startTimeM.value + ":" + SLACtrls.startTimeS.value);
	var endTimeInSec = TimeStrToSec(SLACtrls.endTimeH.value + ":" + SLACtrls.endTimeM.value + ":" + SLACtrls.endTimeS.value);	
	var txName = SLACtrls.txList[SLACtrls.txList.selectedIndex].innerText;
	
	resStr = "sla_invoke_analyze_tx:";

	// Valid input
	if(validityCode == 0)
	{
		resStr = resStr + "valid:" + String(txName) + ":" + String(startTimeInSec) + ":" + String(endTimeInSec);
		window.navigate(resStr);
		return false;
	}
	
	//	If we have reached here then the input is invalid
	resStr = resStr + "invalid:";

	if(validityCode == 1)
	{
		resStr = resStr + "The specified start time(From) is greater than the end time(To)";
	}

	if(validityCode == 2)
	{
		resStr = resStr + "The specified start time(From) is invalid. Make sure it is within range.";
	}

	if(validityCode == 3)
	{
		resStr = resStr + "The specified end time(To) is invalid. Make sure it is within range.";
	}


	window.navigate(resStr);

	return false;
}