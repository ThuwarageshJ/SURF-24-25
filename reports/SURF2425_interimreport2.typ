#import "@preview/rubber-article:0.3.1": *
#set text(lang:"en")
#set smartquote(enabled: false)
// #import "@preview/unify:0.7.0": num,qty,numrange,qtyrange
// #set math.equation(numbering: "(1)")
#import "@preview/tablex:0.0.9": tablex, colspanx, rowspanx

#show: article.with(
  show-header: true,
  header-titel: "SURF Proposal",
  eq-numbering: "(1.1)",
  eq-chapterwise: true,
  bibliography: bibliography("refs.bib"),
  bib-titel: "References",
  lang: "en"
)


#maketitle(
  title: "Optimization of Experimental Parameters for probing sub-GeV Dark Matter by using Muon Beams at the Light Dark Matter eXperiment (LDMX).\n Interim Report 2 - SURF 2025",

  authors: ("Thuwaragesh Jayachandran",
    ),

  date: datetime.today().display("[day]st [month repr:long] [year]"),

      
)



= Introduction 

The Light Dark Matter eXperiment (LDMX) is a proposed experiment that aims to probe for sub-GeV dark matter through collisions of an electron beam with a fixed target @LDMX:2018cma. It would use the momenta and energies of incoming and outgoing particles to identify any violation of conservation laws, as predicted by the Standard Model, which could be a hint at dark matter. The first stage of LDMX will use an electron beam, but, as explained in Interim Report 1, there are several proposals that have been put forward for using muon beams @LDMX:2018cma, @M3:2018. This project aims to understand several muon production processes and utilize it to design a target and its geometry which could produce muons in a desirable phase-space region whilst minimizing unwanted background processes.


// = Problem and Proposed Approach

Producing a well-characterized muon beam meeting the desired energy, momentum, and angular distributions is the crucial problem addressed in this project. Furthermore, any reasonable production process would also create several background processes which could hinder the functioning of the LDMX setup. Thus, it's also crucial to understand these processes in order to minimize their impact.

In the previous report, it was proposed that we produce muons by shooting an 8 GeV electron beam onto a Tungsten fixed target. The approach proposed was to study the dependence of the emitted muon flux and background flux on target geometry and to identify the optimal configuration. 

= Current Progress

// In the first 3 weeks (summarized in Interim Report 1), we completed some preliminary setups for the analysis. We began by installing _Geant4_ and modelling the target geometry and the incoming electron beam. We then conducted runs of $10^5$ to $10^6$ events to understand the baseline level of muon production. We also studied the inside-target statistics of the produced muons in order to understand the several production processes and the characteristic energies of the produced muons. The conclusion was that an overwhelming number of muons are produced from pion decays, but are unusable for the beam due to their low energies. It was proposed that we study the muon pair production processes since it could produce high energetic muons. However, this process has an extremely low cross section, thus making it harder to collect enough statistics to understand its rareity. 

The work done in the first 3 weeks is summarized in the Interim Report 1. During weeks 4 to 7, the following tasks were completed.

== Implementation of cross-section biasing for the trident process in _Geant4_

To address the challenge of the extremely low cross section for the muon pair (trident) production, we implemented cross-section biasing for the relevant process in our Geant4 simulation. This was achieved by enabling the `G4GenericBiasingPhysics` module and specifically biasing the `"GammaToMuPair"` process for gamma photons. The simulation code was updated to allow toggling of biasing via command-line arguments, and the biasing factor was set to 1000. By utilizing the class used in example GB01 provided by _Geant4_, it is ensured that the statistics of the other processes is unaffected. That is, in order to regain the statistics for muons for the unbiased scenario it is sufficient to divide by the biasing factor. 

== Analysis of the statistics collected from the biased runs

After the cross-section biasing was implemented, runs of $10^5$ to $10^6$ biased events and $10^6$ unbiased events were simulated in order to create datasets for analysis. The numbers from both runs were properly normalized and compared to ensure that the biasing had been properly implemented without affecting any other physical processes in the simulation. These statistics were used to estimate the flux of muons produced per incoming electron, with momenta greater than 2 GeV, which is currently the cut we're using to identify useable muons. The angular distribution of the muons was also analyzed to further understand the direction of the outgoing muons.

To understand the inside-target dynamics of the trident process, we studied the distributions of the muon production coordinates and their displacements inside the target. This gave us a good understanding of how the target thickness might be modified in order to adjust the muon production rates.

== Varying target thickness

Motivated by the results of the previous step, we modified the code to set target thicknesses specified by user input. This enabled us to produce datasets corresponding to target thicknesses of 1 cm, 5 cm, and 10 cm. The square face of the target perpendicular to the beam direction was still kept with a side length of 10 cm. For each of these thicknesses, a run of $10^4$ events was simulated in order to understand the background flux and a run of $10^5$ events was simulated in order to understand the dependence of the muon flux on the target thickness. 

== Further analysis of background processes <cone>

The generated statistics for background processes had several parameters that needed to be taken into consideration: particle type, kinetic energy, flux, direction of momentum, face of the target from which it is emitted, etc. These parameters all play different roles in deciding their impact in the experimental setup, whilst also posing problem of making this multi-dimensional analysis slightly convoluted. Thus, we defined a virtual cube of length 2 m around the target and defined 3 regions on the surface of the cube: front, back, cone. The cone region is the circular projection of a cone of half angle $10 degree$ with its apex at the centre of the target, and its axis along the beam direction. The front region is the region of the cube which is to the forward beam direction from the centre of the target, excluding the cone region. The back region is the rest of the surface of the cube.

By extrapolating the particle trajectories to find the region on the cube on which these particles will enter into, we were able to systematically analyze the background processes. The cone region is the most important one, since it is directly in the beam direction, suggesting that this is the region through which we expect the useable muons to enter the beamline. Thus, any other particles that enter into this region must be filtered out to ensure that only muons are coming out through this region. Therefore, we put more emphasis in understanding this region by subdividing it into smaller cones and analyzing particle fluxes in the cones. 


= Observations and results

The biased simulations generated enough number of muons to statistically estimate the muon flux. The summary of these statistics is shown in @muonsummary below. The 'plus' face refers to the square face that is directly opposite to the face of the tungsten target onto which the incoming electron beam is incident on. The comparison of these rates to the unbiased run are also shown in the table. Although the numbers are quite close to each other, ensuring that the biasing process has provided proper statistics, it's essential to carry out more simulations to estimate the variance in these values.

#figure(
  tablex(
  columns: (auto, auto, auto, auto),
  rowspanx(2)[Muons], colspanx(2)[Biased Run],[
    Unbiased Run],
  [Counts],[Normalized Rate\ (per event)($10^(-6)$)],[Rate \ (per event)($10^(-6)$)],
  [Produced from pion decay],[2344],[2344],[2303],
  [Produced from trident process],[13994],[13.994],[10],
  [Total number],[16338],[2357.994],[2313],
  [Emitted from plus face],[11930],[11.93],[11],
  [Emitted from plus face with $p>2$ GeV ],[2748],[2.748],[2],
  ),
  caption: [
    Summary of the muon production and yield statistics for both biased and unbiased runs. Both runs included $10^6$ events. The 'plus' face refers to the square face that is directly opposite to the face of the tungsten target onto which the incoming electron beam is incident on. The rates for the biased run are normalized to that of unbiased run by dividing by the biasing factor.
  ],
  kind: table
)<muonsummary>

// #figure(
//   table(
//   stroke: 0.5pt,
//   columns: (auto,auto,auto,auto,auto),
//   [],[Unbiased run],[Rate],[Biased run],[Rate (normalizedd)],
//   [Muons produced from pion decay],[],[],[],[],
//   [Muons produced from trident process],[],[],[],[],
//   [Total number],[],[],[],[],
//   [Muons emitted from plus face],[],[],[],[],
//   [Muons of $p>2$ GeV emitted from plus face],[],[],[],[],
//   ),
//   caption: [Summary of the values for the fits]
// )<unbiasedbiased>

The estimated rate of 2 muons of $p>2$ GeV per $10^6$ incoming electrons, is sufficient for conducting the LDMX experiment with $10^(13)$ muons over the course of 3 to 4 years (the electron beamline is expected to have pulses of $10^5$ electrons at MHz frequency). This estimation therefore provides evidence that utilizing tungsten target - electron collisions might be sufficient to produce the required muon yield. However, several more runs need to be simulated in order to validate this conclusion. 

Furthermore, the analysis of the muons' inside-target statistics showed that the muon production through the trident process saturates within the first few centimeters into the cube (@insidetargetmuons). Thus, it is questionable whether we could obtain more muons with higher momenta by using a cube of smaller thickness than 10 cm. On the other hand, reducing the thickness might hinder the experimental setup since it could produce several background particles that are not stopped by the target. This proved that studying the thickness dependence would be a worthy area of exploration.


#figure(
  caption: [Inside-target statistics of muons produced from the trident process. Left: Distribution of the $z-$coordinate where the muons are created. Right: Cumulative distribution of the $z-$coordinates. The $z-$coordinate is the distance of the muon from the target face along the beam direction, measured from the center of the target.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/z_dist_biased_muons.png", width: 90%),
    image("images/z_cumdist_biased_muons.png", width: 90%)
    )
) <insidetargetmuons>

@muonsvsthickness summarizes the muon yield as a function of target thickness (the target's square face dimensions were still kept at 10 cm $times$ 10 cm for this analysis). The yield slightly increases from 1 cm to 5 cm, but does not change much in 10 cm. This could be explained by the right plot of @muonsvsthickness, which proves that a length of slightly more than 1 cm is required for the muon production process to get saturated. Therefore, the 1 cm prism does not provide enough material for the process to complete, whilst around 5 cm the process is almost fully completed. The high energy muons are also not much affected in their momenta when travelling through the rest of the 5 cm of the cube, thus resulting in a similar yield in the 10 cm thickness.

#figure(
  caption: [Muon yield as a function of target thickness. Left: Yield of muons as a function of target thickness. Right: Cumulative distribution of the $z-$coordinates of the muons as a function of target thickness.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/muonflux_vs_thickness.png", width: 90%),
    image("images/z_cumdist_biased_muons_vs_thickness.png", width: 100%)
    )
) <muonsvsthickness>

The regions of the virtual cube defined in @cone were used to analyze the phase space of the background particles. The analysis for electrons (and positrons) represents a typical situation for the other particles (protons, pions, gamma), and is presented in @background below. The energy distribution of the electrons entering the cone provides clear evidence that for smaller thicknesses, a significantly larger number of electrons of significantly higher energies enter the cone.  This suggests that to minimize the background flux entering the cone, the target thickness must be increased. 

#figure(
  caption: [Distributions of electrons and positrons entering the cone region. Left: Cumulative distribution as a function of the cone half-angle. Right: Distribution in kinetic energies.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/electronsincone_vs_thickness.png", width: 90%),
    image("images/electronsincone_E_vs_thickness.png", width: 100%)
    )
) <background>

The analysis of @backgroundphasespace provides further information about these background electrons: the ratio of these particles to the muons is an increasing function of the cone half-angle. From similar data for muons, it is also confirmed that muons of $p>2$ GeV are also entering the cone at really smaller angles (within $5 degree$). That is, to facilitate the filtering process, it is beneficial to utilize a very narrow cone region centred at the target. This reduces the number of background particles entering the cone whilst maintaining the muon yield. The analysis is qualitatively similar to protons, pions and gamma photons. However, it differs slightly for neutrons since their interaction lengths are different. This will be further analyzed in the next steps of the project.

= Next steps

Since the thicknesses tested haven't shown any impact on the muon yield so far whilst showing a significant reduction in the background flux, we next plan to analyze even larger thicknesses. This might help us find the optimal thickness that minimizes the background flux without compromising the muon yield.




#figure(
  caption: [Top: Ratio of electrons and positrons entering the cone to that of the normalized muon counts as a function of the cone half-angle. Bottom: Phase space of the electrons and positrons entering the cone for all 3 thicknesses tested.],
  grid(
    columns:1,
    gutter:0mm,
    image("images/e_per_muons_in_cone_vs_thickness.png", width: 90%),
    image("images/e_phase_space_in_cone_vs_thickness.png", width: 100%)
    )
) <backgroundphasespace>


Following this analysis of target geometry, we expect to have a good understanding of the muon energy and momentum distributions. We plan to perform numerical calculations utilizing these information to understand the sensitivity of the experiment that can be performed. 



= Conclusion

In summary, our analysis demonstrates that increasing the target thickness effectively reduces background particle flux without significantly affecting the muon yield, thereby improving the experimental signal-to-background ratio. These findings provide valuable guidance for optimizing target geometry in future muon production experiments, and set the stage for further studies aimed at maximizing sensitivity and minimizing unwanted backgrounds.







// = References
// @LDMX:2018cma T. Akesson und others, "Light Dark Matter eXperiment (LDMX)", Nr. FERMILAB-PUB-18-324-A,
// SLAC-PUB-17303, 2018, doi: https://doi.org/10.48550/arXiv.1808.05219.

// @M3:2018 Y. Khan und others, "$M^3$
// : A New Muon Missing Momentum Experiment to Probe $(𝑔 − 2)_mu$
//  and
// Dark Matter at Fermilab", Nr. FERMILAB-PUB-18-087-A, PUPT-2557, 2018, doi: https://doi.org/
// 10.1007/JHEP09%282018%29153.

// @MuonDM2017 C.-Y. Chen und others, "Muon Beam Experiments to Probe the Dark Sector", Physical Review
// Letters, 2017, doi: https://doi.org/10.1103/PhysRevD.95.115005.

// #figure(
//   caption: [The Planets of the Solar System and Their Average Distance from the Sun],
//   placement: top,
//   table(
//     // Table styling is not mandated by the IEEE. Feel free to adjust these
//     // settings and potentially move them into a set rule.
//     columns: (6em, auto),
//     align: (left, right),
//     inset: (x: 8pt, y: 4pt),
//     stroke: (x, y) => if y <= 1 { (top: 0.5pt) },
//     fill: (x, y) => if y > 0 and calc.rem(y, 2) == 0  { rgb("#efefef") },

//     table.header[Planet][Distance (million km)],
//     [Mercury], [57.9],
//     [Venus], [108.2],
//     [Earth], [149.6],
//     [Mars], [227.9],
//     [Jupiter], [778.6],
//     [Saturn], [1,433.5],
//     [Uranus], [2,872.5],
//     [Neptune], [4,495.1],
//   )
// ) <tab:planets>
// $ a + b = gamma $ <eq:gamma>



// #figure(
//   placement: none,
//   circle(radius: 10pt),
//   caption: [A circle representing the Sun.]
// ) <fig:sun>

// In @fig:sun you can see a common representation of the Sun, which is a star that is located at the center of the solar system. @M3:2018

// #lorem(120)

// #figure(
//   caption: [The Planets of the Solar System and Their Average Distance from the Sun],
//   placement: top,
//   table(
//     // Table styling is not mandated by the IEEE. Feel free to adjust these
//     // settings and potentially move them into a set rule.
//     columns: (6em, auto),
//     align: (left, right),
//     inset: (x: 8pt, y: 4pt),
//     stroke: (x, y) => if y <= 1 { (top: 0.5pt) },
//     fill: (x, y) => if y > 0 and calc.rem(y, 2) == 0  { rgb("#efefef") },

//     table.header[Planet][Distance (million km)],
//     [Mercury], [57.9],
//     [Venus], [108.2],
//     [Earth], [149.6],
//     [Mars], [227.9],
//     [Jupiter], [778.6],
//     [Saturn], [1,433.5],
//     [Uranus], [2,872.5],
//     [Neptune], [4,495.1],
//   )
// ) <tab:planets>

// In @tab:planets, you see the planets of the solar system and their average distance from the Sun.
// The distances were calculated with @eq:gamma that we presented in @sec:methods.

// #lorem(240)

// #lorem(240)
