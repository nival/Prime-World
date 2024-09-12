var date = new Date();
var currdate = new Date();
var colorclear;
var input;

function insertNodeText(obj, text) {
	var txtNode = document.createTextNode(text);
	obj.appendChild(txtNode);
	return obj;
}

function insertButton(obj, text, flag) {
	var buttons = Array (2);
	for (i = 0; i < buttons.length; i++) {
		button = document.createElement('Button');
		var caption = (i == flag)? text + text : text;
		button = insertNodeText(button, caption);
		button.onclick = controlButton;
		obj.appendChild(button);
	}
}

function getCoords(elem) {
	var box = elem.getBoundingClientRect();
	var scrollTop = window.pageYOffset || document.documentElement.scrollTop || document.body.scrollTop;
 	var scrollLeft = window.pageXOffset || document.documentElement.scrollLeft || document.body.scrollLeft;
 	var clientTop = document.documentElement.clientTop || document.body.clientTop || 0;
 	var clientLeft = document.documentElement.clientLeft || document.body.clientLeft || 0;
	var top  = box.top +  scrollTop - clientTop;
	var left = box.left + scrollLeft - clientLeft;
	return { top: Math.round(top) + elem.offsetHeight + 'px', left: Math.round(left) + 'px'}
}

function getCountDay(index) {
	var months = new Array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
	if (date.getFullYear() % 4 == 0)
		months[1]++;
	return months[index];
}

function getCountWeek(date) {
	date.setDate(1);
	return Math.ceil((getCountDay(date.getMonth()) + getNumberDay(date)) / 7);
}

function getNumberDay(date) {
	var days = new Array(6, 0, 1, 2, 3, 4, 5);
	return days[date.getDay()];
}

function getNumberFirstDay(date) {
	date.setDate(1);
	return getNumberDay(date);
}

function controlButton() {
	if (this.lastChild.nodeValue.length == 1) {
		var m = (this.lastChild.nodeValue == '<')? date.getTime() - (24 * 60 * 60 * 1000 * date.getDate()) : date.getTime() + (24 * 60 * 60 * 1000 * (getCountDay(date.getMonth()) - date.getDate() + 1));
			date.setTime(m);
	}
	else {
		var Y = (this.lastChild.nodeValue == '<<')? date.getFullYear() - 1 : date.getFullYear() + 1;
		date.setFullYear(Y);
	}
	generateCalendar();
}

function createTable() {
	var days = new Array('П', 'В', 'С', 'Ч', 'П','С','В');
	
	body = document.getElementsByTagName('body')[0];
	div = document.createElement('div');
	body.appendChild(div);
	div.setAttribute('id', 'calendar', 0);
	div.className = 'calendar-wrapper';
		
	var tbl = document.createElement("table");
	div.appendChild(tbl);
	
	tbl.setAttribute('align', 'center', 0);
	tbl.setAttribute('cellpadding', '0', 0);
	tbl.setAttribute('cellspacing', '0', 0);	
	
	var row = tbl.insertRow(-1);
	row.setAttribute('id', 'first-child', 0);	
	
	// первая ячейка
	var cell = row.insertCell(-1);
	cell.setAttribute('colspan', '2', 0);
	cell.className = 'lalign';
	cell = insertButton(cell, '<', 0);
	
	// вторая ячейка
	var cell = row.insertCell(-1);
	cell.setAttribute('colspan', '3', 0);	
	
	// третья ячейка
	cell = row.insertCell(-1);
	cell.setAttribute('colspan', '2', 0);	
	cell.className = 'ralign';
	cell = insertButton(cell, '>', 1);
	
	row = tbl.insertRow(-1);
	row.className = 'day';
	for (i = 0; i < 7; i++) {
		cell = row.insertCell(-1);
		cell = insertNodeText(cell, days[i]);
		if (i == 6)
			cell.style.color = '#ee0000';							
	}
}

function generateCalendar() {
	var wrapper = document.getElementById('calendar');
	var tbl = wrapper.getElementsByTagName('table')[0];	
	
	var months = Array('Янв', 'Фев', 'Мар', 'Апр', 'Май', 'Июн', 'Июл', 'Авг', 'Сен', 'Окт', 'Ноя', 'Дек');	
	
	tbl.rows[0].cells[1].innerHTML = months[date.getMonth()] + ' ' + date.getFullYear();
	
	while (tbl.rows.length > 2)
		tbl.deleteRow(tbl.rows.length - 1);
	
	var flag = false;
	var countday = 1;
	
	for (i = 0; i < getCountWeek(date); i++) {
		row = tbl.insertRow(-1);
		for (j = 0; j < 7; j++) {
			cell = row.insertCell(-1);
			if (j == getNumberFirstDay(date))
				flag = true;
			if (flag && countday <= getCountDay(date.getMonth())) {
				cell = insertNodeText(cell, countday);
				
				cell.onclick = function() {
											document.getElementById('calendar').style.display = 'none';
											date.setDate(this.lastChild.nodeValue);
											var d = (date.getDate() < 10)? '0' + date.getDate() : date.getDate();									
											var m = ((date.getMonth() + 1) < 10)? '0' + (date.getMonth() + 1) : (date.getMonth() + 1);
											// Порядок вывода даты (День, Месяц, Год)
											input.value = date.getFullYear() + '-' + m + '-' + d;
											
								};
				cell.onmouseover = function() {colorclear = this.className; this.className = 'Select';};
				cell.onmouseout = function() {this.className = colorclear;};
				if (j == 6)
					cell.className = 'Sunday';
				else
					cell.className = 'DefaultDay';
				if (currdate.getFullYear() == date.getFullYear() && currdate.getMonth() == date.getMonth() && currdate.getDate() == countday)
					cell.className = 'CurrDay';
					
				countday++;
			}
			else {
				cell.style.border = 'none';
				cell = insertNodeText(cell, ' ');
			}
		}
	}
}


function showcalendar(input_date) {
	input = input_date;
	var wrapper = document.getElementById('calendar');
	
	if (input.value != '') {
		// Разделяем переданную дату
		var ar = input.value.split('-');
		// Массив параметров (День, Месяц, Год)
		// В Конструктор Date передаем в другом порядке, а именно: Год, Месяц, День 
		// ar[2] - Год
		// ar[1] - Месяц
		// ar[0] - День
		// В JavaScript месяца идут с 0 до 11, поэтому мы от номера месяца отнимаем единицу
		//date = new Date (ar[2], ar[1] - 1, ar[0]);
		date = new Date (ar[0], ar[1] - 1, ar[2]);
	}
	
	generateCalendar();	
		
	wrapper.style.left = getCoords(input).left ;
	wrapper.style.top = getCoords(input).top;
	wrapper.style.display = (wrapper.style.display=="block")? "none" : "block";
}

if (window.addEventListener)
	window.addEventListener('load', createTable, false);
else if (window.attachEvent)
	window.attachEvent('onload', createTable);