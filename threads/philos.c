
philo(i) {
	while (1) {
		think();
		grab((i-1) % 5);	//grab right chopstick
		grab(i); 		    //grab left chopstick 	
		eat();
		release((i-1) % 5); //release right
		release(i); 		//release left
	}
}
