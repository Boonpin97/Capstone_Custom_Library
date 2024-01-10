#Capstone Custom Library

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 24%" />
<col style="width: 60%" />
</colgroup>
<thead>
<tr class="header">
<th colspan="2"><strong>void move (int target_pos, int spd)</strong></th>
<th>A function that controls the position of the tray. Takes in a position argument and moves the tray according to the position. Every time the tray hits the limit switch, that position will be reset to the new neutral position. Outputs no argument</th>
</tr>
<tr class="odd">
<th rowspan="2"><strong>Input</strong></th>
<th>target_pos (int)</th>
<th>The targeted position of the tray in mm, with a neutral position at value 0. The tray will move to this value’s position. The value ranges from 0-335.</th>
</tr>
<tr class="header">
<th><p>spd (int)</p>
<p>Default value: 500</p></th>
<th>This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start with. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the <strong>higher</strong> the value, the <strong>slower</strong> the tray.</th>
</tr>
<tr class="odd">
<th><strong>Output</strong></th>
<th>current_pos (int)</th>
<th>Returns the updated position of the tray.</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 24%" />
<col style="width: 60%" />
</colgroup>
<thead>
<tr class="header">
<th colspan="2"><strong>void resetFront (int spd)</strong></th>
<th>A function that resets the position of the tray. This function moves the tray to the <strong>front</strong> and stops.</th>
</tr>
<tr class="odd">
<th><strong>Input</strong></th>
<th><p>spd (int)</p>
<p>Default value: 500</p></th>
<th>This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start with. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the <strong>higher</strong> the value, the <strong>slower</strong> the tray</th>
</tr>
<tr class="header">
<th><strong>Output</strong></th>
<th>current_pos (int)</th>
<th>Returns the updated position of the tray</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 24%" />
<col style="width: 60%" />
</colgroup>
<thead>
<tr class="header">
<th colspan="2"><strong>void resetBack (int spd)</strong></th>
<th>A function that resets the position of the tray. This function moves the tray to the <strong>back</strong> and stops.</th>
</tr>
<tr class="odd">
<th><strong>Input</strong></th>
<th><p>spd (int)</p>
<p>Default value: 500</p></th>
<th>This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the <strong>higher</strong> the value, the <strong>slower</strong> the tray</th>
</tr>
<tr class="header">
<th><strong>Output</strong></th>
<th>current_pos (int)</th>
<th>Returns the updated position of the tray</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

| **float\* readLuxs()** |                 | A function that cycles through each port of the multiplexer, reads the light sensor values connected to individual ports and stores them inside an array. Outputs the pointer address of the array. |
|------------------------|-----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Input**              | \-              | \-                                                                                                                                                                                                  |
| **Output**             | array (float\*) | a pointer to an array of size 9, that contains the lux readings of the 9 light sensors                                                                                                              |
