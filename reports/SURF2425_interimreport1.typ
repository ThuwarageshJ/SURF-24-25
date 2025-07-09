#import "@preview/rubber-article:0.3.1": *
#set text(lang:"en")
#set smartquote(enabled: false)
// #import "@preview/unify:0.7.0": num,qty,numrange,qtyrange
// #set math.equation(numbering: "(1)")


#show: article.with(
  show-header: true,
  header-titel: "SURF Proposal",
  eq-numbering: "(1.1)",
  eq-chapterwise: true,
  bibliography: bibliography("refs.bib"),
  bib-titel: "References"
)


#maketitle(
  title: "Optimization of Experimental Parameters for probing sub-GeV Dark Matter by using Muon Beams at the Light Dark Matter eXperiment (LDMX).\n Interim Report 1 - SURF 2025",

  authors: ("Thuwaragesh Jayachandran",
    ),

  date: datetime.today().display("[day]th [month repr:long] [year]"),

      
)



= Motivation and Background

The Light Dark Matter eXperiment (LDMX) is a proposed experiment that aims to probe for sub-GeV dark matter through collisions of electron beam with a fixed target @LDMX:2018cma. By tracking of the incoming and outgoing particles to monitor their momenta, and precisely measuring the energy deposits using electromagnetic and hadronic calorimeters, the experiment will attempt to veto out all of known standard model processes. Any missing momentum or missing energy for which a standard model process cannot be attributed will be an indication of the existence of matter that is not predicted by the standard model -- which could possibly be dark matter.
 

Both the LDMX @LDMX:2018cma and $M^3$ @M3:2018 proposals advocate extending LDMX to use muon beams, motivated by their potential to address muon physics anomalies, probe muon-philic forces, and explore dark sectors that couple preferentially to second-generation Standard Model particles @MuonDM2017. Muons, unlike electrons, lose less energy via bremsstrahlung, enabling deeper penetration and higher interaction rates with dark sector mediators, and are thus well-suited for probing heavier dark matter candidates. Experimentally, muon beams offer significant advantages: bremsstrahlung backgrounds are suppressed by a factor of about $(m_e/m_mu)^2 approx 2 times 10^(-5)$, greatly reducing challenging backgrounds for LDMX calorimetry @LDMX:2018cma, and allow for percent-level momentum resolution with a magnetized target, collectively promising increased experimental sensitivity over electron beams.

The LDMX proposal is soon to be submitted and constructions are expected to begin in the upcoming year.

= Problem

The ability to generate a well-characterized muon beam is critical for achieving the above mentioned goals. One promising method is to directly generate muons in electron-fixed target collisions. When a high-energy electron beam strikes a dense material such as tungsten, it produces pairs of charged muons. A key challenge is the efficiency of muon production. For comparison, a 4 GeV electron beam has a muon production rate of only around $10^(-6)$ when using the LDMX fixed target @LDMX:2018cma. Indeed, muons lose much energy compared to electrons when penetrating through targets of same radiation lengths @M3:2018.

= Proposed Approach 

To solve the problem of efficiency and characterization in muon beam production it is essential to  carefully study the target material's geometry and composition. We have planned to model and simulate the production of muons from electron-target collisions using _Geant4_, a widely used particle physics simulation toolkit. 

The proposed approach is to begin by studying the outcomes of bombarding an 8 GeV electron beam onto a standard Tungsten cube of length 10 cm. Using _Geant4_ simulations, we will model the interactions between the electron beam and the tungsten target to quantify the resulting muon production rates, energy spectra, and angular distributions. This initial study will serve as a baseline for comparison as we systematically vary target parameters such as thickness, shape, and material composition. 

Another proposed angle of attack is to study the physical processes that are expected to produce muons in the setup. By analyzing the frequency of intermediate processes leading to muon production, the interaction lengths of particles involved in such processes, we aim to systematically modify the Tungsten target geometry and accelerate such processes. The results will inform subsequent optimization steps aimed at maximizing muon yield while considering practical constraints such as target heating, radiation damage, and integration with the LDMX experimental setup.

= Current Progress

In the first 3 weeks, we have completed the following steps in the proposed approach.

== Software installation and modeling the experimental setup

Our initial steps involved installing _Geant4_ and developing the necessary code to simulate the experimental setup. The current configuration features a 10 cm-sided tungsten cube serving as the fixed target for the electron beam. To replicate LDMX conditions, the beam is simulated to emit single 8 GeV electrons per event from a randomly chosen point within a 3 cm $times$ 8 cm area, aimed at the center of the cube’s face. For statistical purposes, we have conducted runs of $10^5$ to $10^6$ events.

== Initial runs with naive conditions

To assess the baseline level of muon production, we conducted 2 runs with the above mentioned setup. The detector was setup to track particles coming out of the cube in all directions and their physical properties (kinetic energy at surface, momentum at surface, and angle of emission). The first run with $10^4$ events produced no muons and the second run with $10^5$ events produced 2 $mu^+$ particles. These particles had energies and momenta of (50 MeV, 120 MeV) and (3 MeV, 25 MeV) and angles of $theta=110 degree$ and $theta=170 degree$ respectrively (measured with respect to the beam direction). These conditions are not optimal for the GeV-scale muons expected for the LDMX beam. The angles were also identified to be suboptimal since they indicate that the particles are highly diverging from the beam direction.

Two modifications to the analysis and simulations were proposed at this stage. The first one focuses on understanding the relative frequencies of several muon production processes taking place inside the target. We decided to track and store the data for all the processes involving muons and pions (which are expected to decay into muons) along with the processes that created or killed those particles. This modification could help in understanding the physical processes of interest which then could inform about the changes required to be done for the target geometry to increase the outputs of such processes.

The second proposed modification aims on increasing the statistical accuracy of the results of this and future simulations. Since _Geant4_ enables artifically biasing the cross sections for certain events, we can increase the probability of muon production processes by a large factor. Although this is not a feasible in real life, increasing the muon production in simulations will be an important step in accumulating the necessary statistics to justify the validity of the conclusions derived above and in the future. 

== Analysis of physical processes inside the target

The first of the above mentioned modifications







= Challenges

= (Immediate) Future Directions


= Conclusion



= References
@LDMX:2018cma T. Akesson und others, "Light Dark Matter eXperiment (LDMX)", Nr. FERMILAB-PUB-18-324-A,
SLAC-PUB-17303, 2018, doi: https://doi.org/10.48550/arXiv.1808.05219.

@M3:2018 Y. Khan und others, "$M^3$
: A New Muon Missing Momentum Experiment to Probe $(𝑔 − 2)_mu$
 and
Dark Matter at Fermilab", Nr. FERMILAB-PUB-18-087-A, PUPT-2557, 2018, doi: https://doi.org/
10.1007/JHEP09%282018%29153.

@MuonDM2017 C.-Y. Chen und others, "Muon Beam Experiments to Probe the Dark Sector", Physical Review
Letters, 2017, doi: https://doi.org/10.1103/PhysRevD.95.115005.

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
