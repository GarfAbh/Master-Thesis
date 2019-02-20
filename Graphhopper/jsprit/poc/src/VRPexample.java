

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;


import com.graphhopper.jsprit.analysis.toolbox.AlgorithmSearchProgressChartListener;
import com.graphhopper.jsprit.analysis.toolbox.StopWatch;
import com.graphhopper.jsprit.core.algorithm.VehicleRoutingAlgorithm;
import com.graphhopper.jsprit.core.algorithm.box.Jsprit;
import com.graphhopper.jsprit.core.algorithm.listener.VehicleRoutingAlgorithmListeners;
import com.graphhopper.jsprit.core.problem.Location;
import com.graphhopper.jsprit.core.problem.VehicleRoutingProblem;
import com.graphhopper.jsprit.core.problem.job.Service;
import com.graphhopper.jsprit.core.problem.solution.VehicleRoutingProblemSolution;
import com.graphhopper.jsprit.core.problem.solution.route.activity.TimeWindow;
import com.graphhopper.jsprit.core.problem.vehicle.VehicleImpl;
import com.graphhopper.jsprit.core.problem.vehicle.VehicleType;
import com.graphhopper.jsprit.core.problem.vehicle.VehicleTypeImpl;
import com.graphhopper.jsprit.core.reporting.SolutionPrinter;
import com.graphhopper.jsprit.core.util.Coordinate;
import com.graphhopper.jsprit.core.util.Solutions;
import com.graphhopper.jsprit.util.Examples;


import java.util.Collection;
import java.util.Random;
import java.util.regex.*;


public class VRPexample {
    public static void main(String[] args) throws IOException {
        System.out.println("hello world");
        Examples.createOutputFolder();

        VehicleRoutingProblem.Builder vrpBuilder = VehicleRoutingProblem.Builder.newInstance();
        vrpBuilder.setFleetSize(VehicleRoutingProblem.FleetSize.FINITE);

        /**
         * args[0] = nb jobs
         * args[1] = nb_threads;
         * args[2] = lausanne VS switzerland
         * args[3] = random de time windowed or not
         * args[4] = la seed pour le random.
         */
        if(args.length != 5){
            System.out.println("y a un soucis avec les argument il en faut 4");
            System.out.println("usage : ./poc [nb_job] [nb_threads][Lausanne/Swiss] [true/false] [seed]");
        }

        int nb_jobs = Integer.parseInt(args[0]);
        String country_test = args[2];
        Boolean ra = Boolean.parseBoolean(args[3]);
        Random rand = new Random(Long.parseLong(args[4]));

        set_vehicle(vrpBuilder);
        set_jobs(vrpBuilder,nb_jobs,country_test,ra,rand);

        VehicleRoutingProblem vrp = vrpBuilder.build();
        VehicleRoutingAlgorithm vra = Jsprit.Builder.newInstance(vrp).setProperty(Jsprit.Parameter.THREADS,args[1]).buildAlgorithm();
        vra.getAlgorithmListeners().addListener(new StopWatch(),VehicleRoutingAlgorithmListeners.Priority.HIGH);
        //vra.getAlgorithmListeners().addListener(new AlgorithmSearchProgressChartListener("output/poc.png"));
        Collection<VehicleRoutingProblemSolution> solutions = vra.searchSolutions();

        SolutionPrinter.print(Solutions.bestOf(solutions));
    }

    //Permet de set le / les vehicule pour le problème
    public static void set_vehicle(VehicleRoutingProblem.Builder vrpBuilder){
        int capacity = 100;
        //il s'agit de chez altux et chez moi
        Coordinate DepotCoord = Coordinate.newInstance(6.68973, 46.50190);
        Coordinate maison = Coordinate.newInstance(6.64357,46.50910);

        String typeId = "test_type";
        VehicleType vehicleType = VehicleTypeImpl.Builder.newInstance(typeId).addCapacityDimension(0, capacity).setCostPerDistance(1.0).build();
        String vehicleId = "1";
        VehicleImpl.Builder vehicleBuilder = VehicleImpl.Builder.newInstance(vehicleId);
        vehicleBuilder.setStartLocation(Location.newInstance(DepotCoord.getX(), DepotCoord.getY()));  //defines the location of the vehicle and thus the depot
        vehicleBuilder.setEndLocation(Location.newInstance(maison.getX(),maison.getY()));
        vehicleBuilder.setEarliestStart(28800);
        vehicleBuilder.setLatestArrival(61200);
        vehicleBuilder.setType(vehicleType);
        VehicleImpl vehicle = vehicleBuilder.build();
        vrpBuilder.addVehicle(vehicle);
    }
    //permet de set les jobs du problème.
    public static void set_jobs(VehicleRoutingProblem.Builder vrpBuilder,int nb_jobs,String country,Boolean ra,Random rand) throws IOException {
        for (int i = 0 ; i < nb_jobs ; i++){
            if(rand.nextInt(101) <= 20 && ra){
                //TODO set avec une time window
                Service.Builder serviceBuilder = Service.Builder.newInstance(Integer.toString(i));
                serviceBuilder.setLocation(get_random_addr(country,rand));
                Service service = serviceBuilder.build();
                vrpBuilder.addJob(service);
            }else{
                //TODO set sans time window
                Service.Builder serviceBuilder = Service.Builder.newInstance(Integer.toString(i));
                serviceBuilder.setLocation(get_random_addr(country,rand));
                serviceBuilder.addTimeWindow(TimeWindow.newInstance(28800,36000));
                Service service = serviceBuilder.build();
                vrpBuilder.addJob(service);
            }
        }
    }
    public static Location get_random_addr(String country,Random rand) throws IOException {
        double lon, lat;


        lon = get_random_long_lat(country, rand, true);
        lat = get_random_long_lat(country, rand, false);
        String u = "http://localhost:8989/nearest/?point=" + Double.toString(lat) + "," + Double.toString(lon) + "";
        URL url = new URL(u);
        String line ;
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream(), "UTF-8"))) {
            line = reader.readLine();
        }
        System.out.println(line);
        String match1 = line.split("]")[0];
        String match2 = match1.split("\\[")[1];
        String longi = match2.split(",")[0];
        String lati = match2.split(",")[1];
        return Location.newInstance(Double.parseDouble(longi),Double.parseDouble(lati));
        //return Location.newInstance(6.54848,46.62047);
    }
    public static double get_random_long_lat(String country, Random rand,Boolean lon){
        double max_lon, min_lon, max_lat, min_lat;
        if(country.compareTo("lausanne") == 0){
            max_lat = 46.5845;
            min_lat = 46.5845;

            max_lon = 6.732;
            min_lon = 6.5075;
        }else{
            max_lat = 47.80842;
            min_lat = 45.818;

            max_lon = 10.492;
            min_lon = 5.956;
        }
        double range;
        if(lon){
            range = max_lon - min_lon;
            return rand.nextDouble() * range + min_lon;
        }else{
            range = max_lat - min_lat;
            return rand.nextDouble() * range + min_lat;
        }
    }

}
