/*  This file is part of Openrouteservice.
 *
 *  Openrouteservice is free software; you can redistribute it and/or modify it under the terms of the 
 *  GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 
 *  of the License, or (at your option) any later version.

 *  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *  See the GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License along with this library; 
 *  if not, see <https://www.gnu.org/licenses/>.  
 */
package heigit.ors.routing.graphhopper.extensions.flagencoders.bike;

import com.graphhopper.util.PMap;
import heigit.ors.routing.graphhopper.extensions.flagencoders.FlagEncoderNames;

public class ElectroBikeFlagEncoder extends CommonBikeFlagEncoder
{
	  
    public ElectroBikeFlagEncoder()
    {
        this(4, 2, 0, false);
    }

    public ElectroBikeFlagEncoder( String propertiesString )
    {
        this(new PMap(propertiesString));
    }

    public ElectroBikeFlagEncoder(PMap properties )
    {
        this((int) properties.getLong("speed_bits", 4) + (properties.getBool("consider_elevation", false) ? 1 : 0),
                properties.getLong("speed_factor", 2),
                properties.getBool("turn_costs", false) ? 1 : 0, properties.getBool("consider_elevation", false));
        this.properties = properties;
        this.setBlockFords(properties.getBool("block_fords", true));
    }
    
    public ElectroBikeFlagEncoder( int speedBits, double speedFactor, int maxTurnCosts)
    {
      this(speedBits, speedFactor, maxTurnCosts, false);
    }

    public ElectroBikeFlagEncoder( int speedBits, double speedFactor, int maxTurnCosts, boolean considerElevation)
    {
        super(speedBits, speedFactor, maxTurnCosts, considerElevation);

        // preferHighwayTags.add("road");
        preferHighwayTags.add("service");
        preferHighwayTags.add("tertiary");
        preferHighwayTags.add("tertiary_link");
        preferHighwayTags.add("residential");
        preferHighwayTags.add("unclassified");

        setTrackTypeSpeed("grade1", 21); // paved
        setTrackTypeSpeed("grade2", 15); // now unpaved ...
        setTrackTypeSpeed("grade3", 9);
        setTrackTypeSpeed("grade4", 7);
        setTrackTypeSpeed("grade5", 4); // like sand/grass

        setSurfaceSpeed("paved", 21);
        setSurfaceSpeed("asphalt", 21);
        setSurfaceSpeed("cobblestone", 9);
        setSurfaceSpeed("cobblestone:flattened", 11);
        setSurfaceSpeed("sett", 11);
        setSurfaceSpeed("concrete", 21);
		setSurfaceSpeed("concrete:lanes", 18);
		setSurfaceSpeed("concrete:plates", 18);
		setSurfaceSpeed("paving_stones", 13);
		setSurfaceSpeed("paving_stones:30", 13);
		setSurfaceSpeed("unpaved", 15);
		setSurfaceSpeed("compacted", 17);
		setSurfaceSpeed("dirt", 11);
		setSurfaceSpeed("earth", 13);
		setSurfaceSpeed("fine_gravel", 19);
		setSurfaceSpeed("grass", 9);
		setSurfaceSpeed("grass_paver", 9);
		setSurfaceSpeed("gravel", 13);
		setSurfaceSpeed("ground", 13);
		setSurfaceSpeed("ice", PUSHING_SECTION_SPEED / 2);
		setSurfaceSpeed("metal", 11);
		setSurfaceSpeed("mud", 11);
		setSurfaceSpeed("pebblestone", 18);
		setSurfaceSpeed("salt", 7);
		setSurfaceSpeed("sand", 7);
		setSurfaceSpeed("wood", 7);

        setHighwaySpeed("living_street", 9);
        setHighwaySpeed("steps", PUSHING_SECTION_SPEED/2);
        setHighwaySpeed("cycleway", 21);
        setHighwaySpeed("path", 13);
        setHighwaySpeed("footway", 7);
        setHighwaySpeed("pedestrian", 7);
        setHighwaySpeed("road", 14);
        setHighwaySpeed("track", 13);
        setHighwaySpeed("service", 15);
        setHighwaySpeed("unclassified", 18);
        setHighwaySpeed("residential", 21);

        setHighwaySpeed("trunk", 20);
        setHighwaySpeed("trunk_link", 20);
        setHighwaySpeed("primary", 21);
        setHighwaySpeed("primary_link", 21);
        setHighwaySpeed("secondary", 21);
        setHighwaySpeed("secondary_link", 21);
        setHighwaySpeed("tertiary", 21);
        setHighwaySpeed("tertiary_link", 21);
        
        addPushingSection("path");
        addPushingSection("footway");
        addPushingSection("pedestrian");
        addPushingSection("steps");

        avoidHighwayTags.add("trunk");
        avoidHighwayTags.add("trunk_link");
        avoidHighwayTags.add("primary");
        avoidHighwayTags.add("primary_link");
        avoidHighwayTags.add("secondary");
        avoidHighwayTags.add("secondary_link");

        absoluteBarriers.add("kissing_gate");

        setSpecificClassBicycle("touring");

        // MARQ24 -> till here this will just overwite the default values of the common bike flag encoder...

        this.init();
    }

    @Override
    public int getVersion()
    {
        return 2;
    }

    /*@Override
    protected boolean isPushingSection(ReaderWay way )
    {
        String highway = way.getTag("highway");
        String trackType = way.getTag("tracktype");
        return way.hasTag("highway", pushingSectionsHighways)
                || way.hasTag("railway", "platform")  || way.hasTag("route", ferries)
                || "track".equals(highway) && trackType != null 
            	&&  !("grade1".equals(trackType) || "grade2".equals(trackType) || "grade3".equals(trackType)); // Runge
    }*/
    
    @Override
	protected double getDownhillMaxSpeed()
	{
		return 30;
	}
    
    /* MARQ24 getGradientSpeed is currently not implemented in any of the bike flag encoder - simply
    // cause we get always this detours...
	protected double getGradientSpeed(double speed, int gradient)
	{
    	if (speed > 10)
    		return speed + getGradientSpeedChange(gradient);
    	else
    	{
    		double result = speed + getGradientSpeedChange(gradient);

    		// forbid high downhill speeds on surfaces with low speeds
    		if (result > speed)
    			return speed;
    		else
    			return result;
    	}
	}	
    
    private double getGradientSpeedChange(int gradient)
    {
    	if (gradient > 12)
    		gradient = 12;
    	else if (gradient < -12)
    		gradient = -12;
    	
    	return -0.28*gradient;
    }
    */

    @Override
    public String toString()
    {
        return FlagEncoderNames.BIKE_ELECTRO;
    }
}
