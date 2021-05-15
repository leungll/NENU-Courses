	var selectedObjName = "timeS";
	var defaultName = "timeS"
	var minValue = 0;
	var minsec_maxValue = 59;
	var hrs_maxValue = 999;
	//var scrollTopValue = 1;
	var lastValue = null;
	var lastKeyCode = null;
	
	function JSTrim(p_strToBeTrimmed)
	{
		var vChar
		var vLength
		var i
		var vFirstNotSpace
		var vLastNotSpace
			
		vLength = p_strToBeTrimmed.length
		
		for (i = 0; i < vLength;i++)
		{
			vChar = p_strToBeTrimmed.charAt(i)
			if (vChar != " ")
			{
				vFirstNotSpace = i
				i = vLength
			}
		}
			
		for (i = vLength-1 ; i>=0;i--)
		{
			vChar = p_strToBeTrimmed.charAt(i)
			if (vChar != " ")
			{
				vLastNotSpace = i
				i = -1
			}
		}
		return p_strToBeTrimmed.substring(vFirstNotSpace,vLastNotSpace+1);
	}
	
	
	function EventSelect(obj)
	{
		selectedObjName = obj.name;
	}	
	
	function EventDown(obj)
	{
		selectedObjName = obj.name;
	}
	
	
	function EventKeyUp(obj)
	{
		var newVal = obj.value;
		var maxVal;
		
		if(obj.maxLength == 2)
			maxVal = minsec_maxValue;
		else
			maxVal = hrs_maxValue;
		
		if(newVal > maxVal)	{
			obj.value = lastValue;
		}
	}
	
	function EventKeyPress(obj)
	{
		//alert(window.event.keyCode);
		selectedObjName = obj.name;
		
		var maxVal;
		
		if(obj.maxLength == 2)
			maxVal = minsec_maxValue;
		else
			maxVal = hrs_maxValue;
		
		if(obj.value < maxVal + 1)	{
			lastValue = obj.value;
		}
		
		if(window.event.keyCode < 48 || window.event.keyCode > 57)	{
			window.event.returnValue = false;
		}
	}
	function SetName(name)
	{
		if(selectedObjName.indexOf(name) < 0)
		{
			selectedObjName = name + defaultName;
		}
	}
	
	function EventKeyDown(obj)
	{
		//alert(window.event.keyCode);
		var button_clicked;
		lastKeyCode = window.event.keyCode;
		
		//Arrow Up
		if(window.event.keyCode == 38)	{
			ClickUp();
		}
		
		//Arrow Down
		if(window.event.keyCode == 40)	{
			ClickDown();
		}		
	}
	
	function EventBlur(obj)
	{
		var newVal = obj.value;
		
		var maxVal;
		
		if(obj.maxLength == 2)
			maxVal = minsec_maxValue;
		else
			maxVal = hrs_maxValue;
		
		if(newVal > maxVal)	
		{
			obj.value = lastValue;
		}
		clearLook(obj);		
	}
	
	function clearLook(obj)
	{
		if(obj.maxLength == 2)
		{
			if(JSTrim(obj.value) == "")	
				obj.value = "00";
		
			if(obj.value < 10 && obj.value.length == 1)	
				obj.value = "0" + obj.value;
		}
		
		if(obj.maxLength == 3)
		{
			if(JSTrim(obj.value) == "")	
				obj.value = "000";
				
			if(obj.value < 10 && obj.value.length == 1)	
				obj.value = "00" + obj.value;
			else
			{
				if(obj.value < 100 && obj.value.length == 2)
					obj.value = "0" + obj.value;
			}
		}
	}
	
	
	function EventWheel(obj)
	{
		if (window.event.wheelDelta >= 120)	{
        	if(obj.value < 59)	{
				obj.value++;
				clearLook(obj)
			}
		}
	    else if (event.wheelDelta <= -120)	{
	       if(obj.value > 0)	{
				obj.value--;   
				clearLook(obj)
			}
		}
	}
	
	function ClickUp()
	{
		var obj = document.getElementById(selectedObjName);
		if(selectedObjName.indexOf("timeM") > 0 || selectedObjName.indexOf("timeS") > 0)	
		{
			if(obj.value == 59)		
			{
				obj.value = "00";
				return;
			}
		}
		
		if(selectedObjName.indexOf("timeH") > 0)	
		{
			if(obj.value == 999)		
			{
				obj.value = "000";
				return;
			}
		}
		
		obj.value++;
		clearLook(obj);
	}
	
	function ClickDown()
	{
		var obj = document.getElementById(selectedObjName);
		
		if(selectedObjName.indexOf("timeM") > 0 || selectedObjName.indexOf("timeS") > 0)	
		{
			if(obj.value == 00 || obj.value == 0)		
			{
				obj.value = "59";
				return;
			}
		}
		
		if(selectedObjName.indexOf("timeH") > 0)	
		{
			if(obj.value == 000 || obj.value == 00 || obj.value == 0)		
			{
				obj.value = "999";
				return;
			}
		}
		
		
		/*
		else if(selectedObjName.indexOf("timeH") > 0)		{
			if(obj.value == 00 || obj.value == 0)		{
				obj.value == 00;
				return;
			}
		}
		*/
		obj.value--;
		clearLook(obj);
	}