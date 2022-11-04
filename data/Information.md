# Information of Data Sets


## airports.dat.txt

As of January 2017, the OpenFlights Airports Database contains over 10,000 airports, train stations and ferry terminals spanning the globe, as shown in the map above. Each entry contains the following information:

`Airport ID`	Unique OpenFlights identifier for this airport.

`Name`	Name of airport. May or may not contain the City name.

`City`	Main city served by airport. May be spelled differently from Name.

`Country`	Country or territory where airport is located. See Countries to cross-reference to ISO 3166-1 codes.

`IATA`	3-letter IATA code. Null if not assigned/unknown.

`ICAO`	4-letter ICAO code.
Null if not assigned.

`Latitude`	Decimal degrees, usually to six significant digits. Negative is South, positive is North.

`Longitude`	Decimal degrees, usually to six significant digits. Negative is West, positive is East.

`Altitude`	In feet.

`Timezone`	Hours offset from UTC. Fractional hours are expressed as decimals, eg. India is 5.5.

`DST`	Daylight savings time. One of E (Europe), A (US/Canada), S (South America), O (Australia), Z (New Zealand), N (None) or U (Unknown). See also: Help: Time
Tz database time zone	Timezone in "tz" (Olson) format, eg. "America/Los_Angeles".

`Type`	Type of the airport. Value "airport" for air terminals, "station" for train stations, "port" for ferry terminals and "unknown" if not known. In airports.csv, only type=airport is included.

`Source`	Source of this data. "OurAirports" for data sourced from OurAirports, "Legacy" for old data not matched to OurAirports (mostly DAFIF), "User" for unverified user contributions. In airports.csv, only source=OurAirports is included.

The data is UTF-8 encoded.

## route.dat.txt

As of June 2014, the OpenFlights/Airline Route Mapper Route Database contains 67663 routes between 3321 airports on 548 airlines spanning the globe, as shown in the map above. Each entry contains the following information:

`Airline`	2-letter (IATA) or 3-letter (ICAO) code of the airline.

`Airline ID`	Unique OpenFlights identifier for airline (see Airline).

`Source airport`	3-letter (IATA) or 4-letter (ICAO) code of the source airport.

`Source airport ID`	Unique OpenFlights identifier for source airport (see Airport)

`Destination airport`	3-letter (IATA) or 4-letter (ICAO) code of the destination airport.

`Destination airport ID`	Unique OpenFlights identifier for destination airport (see Airport)

`Codeshare`	"Y" if this flight is a codeshare (that is, not operated by Airline, but another carrier), empty otherwise.

`Stops`	Number of stops on this flight ("0" for direct)

`Equipment`	3-letter codes for plane type(s) generally used on this flight, separated by spaces

The data is UTF-8 encoded. The special value \N is used for "NULL" to indicate that no value is available, and is understood automatically by MySQL if imported.
