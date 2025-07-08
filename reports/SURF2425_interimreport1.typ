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

= Challenges

By analyzing different configurations and geometries of the tungsten target, we aim to determine the optimal setup that maximizes muon production while maintaining experimental feasibility.

While this is the most straightforward way of muon-beam production inspired from the LDMX setup, we also aim to explore other ways of muon production and access their feasibility constraints in search of the most efficient and well-suited production method. Another possibility would be the production of muons through secondary processes: the electron-fixed target collisions can produce kaons and pions which can subsequently decay into muons.

This research aligns with ongoing efforts in experimental particle physics to develop novel methods for dark matter searches. If successful, the results of this study could contribute to the design of a next-generation LDMX-style experiment utilizing muon beams, thereby expanding the search for new physics beyond the Standard Model.



= Approach <sec:methods>


To accomplish the objectives of this study, we will follow a two-phase approach: first, evaluating various muon production methods applicable to the LDMX setup, and second, optimizing the tungsten fixed target geometry using _Geant4_ simulations to maximize muon yield.  

The first phase will involve a detailed analysis of different muon production mechanisms, including direct muon pair production from electron-nucleus interactions and secondary muon production via pion and kaon decays. We will assess these methods based on their feasibility within the LDMX framework, expected muon flux, and experimental constraints such as target thickness and energy losses. A literature review and preliminary calculations will guide this evaluation.  

In the second phase, we will implement a _Geant4_-based simulation framework to model electron-fixed target interactions, tracking muon production rates under different target configurations. Key parameters to be optimized include the thickness, shape, and composition of the tungsten target, as well as the beam energy and angular spread. If time permits, we will extend our optimization to the beam line to further enhance muon yield. The simulation results will be analyzed to identify configurations that offer the highest muon production efficiency while remaining experimentally viable.  

// The most challenging aspect of this project will likely be achieving sufficient statistical accuracy in the _Geant4_ simulations due to the inherently low probability of muon production in electron-fixed target collisions. To address this, we will employ variance reduction techniques such as importance sampling and biasing to improve computational efficiency.  

This research will be conducted in collaboration with Professor Echenard's and Professor Hitlin's groups, which have expertise in LDMX physics and _Geant4_ simulations. If applicable, our work may also depend on input from related studies exploring muon beams in fixed-target experiments.  

By systematically comparing muon production methods and refining target configurations through simulation, this project aims to provide concrete insights into the feasibility of a muon-beam-based extension of LDMX, potentially informing future experimental designs.

= Work Plan
- Week 0: Installing _Geant4_ and getting familiarized with it.
- Week 1: Literature review of Muon production methods and      their feasibility and efficiency constraints.
- Weeks 2-4: Development of required geometries of the Tungsten fixed target and collision physics in _Geant4_.
- Weeks 5-6: Producing datasets and simulations for testing the developed geometries of the target collisions.
- Weeks 7-9: Data analysis from all the simulations, calculations of efficiencies, and progress towards figuring out efficient frameworks of muon production.
- Week 10: Conclusions and final decisions. Preparing the report.

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
