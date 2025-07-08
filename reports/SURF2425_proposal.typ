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
  title: "Optimization of Experimental Parameters for probing sub-GeV Dark Matter by using Muon Beams at the Light Dark Matter eXperiment (LDMX)",
  authors: ("Thuwaragesh Jayachandran",),

  date: datetime.today().display("[month repr:long] [year]"),

      
)

= Introduction
While numerous direct and indirect dark matter detection experiments have been conducted, their precise nature remains elusive. The Light Dark Matter eXperiment (LDMX) is a proposed experiment designed to search for sub-GeV dark matter by electron-fixed target collisions @LDMX:2018cma. LDMX features a multi-GeV electron beam incident on a thin Tungsten fixed target, which is expected to produce Dark Matter particles, mediator particles, and several other background processes @LDMX:2018cma. By vetoing most of the background processes using electromagnetic and hadronic calorimeters, and precisely measuring the missing energy and momentum of the incident electrons, several distinguishing features of MeV to GeV dark matter reactions  can be probed to high sensitivities @LDMX:2018cma. 

The LDMX proposal @LDMX:2018cma and the $M^3$ proposal @M3:2018, had both proposed the idea of extending the capabilities of LDMX to include a muon beam. This roots from the numerous well-motivated science goals that can be achieved using muon beams. Muon beams could help resolve anomalies of muon physics and explore muon-philic forces. The $~4 sigma$ discrepancy in the magnetic moment of muons, along with a well-motivated class of models in which dark matter interact with muons through a muon-exclusive force carrier enabling thermal freeze out reactions, suggest the presence of a muon-philic force carrier @M3:2018 @MuonDM2017. Also, more importantly, muon beams can explore dark sectors whose particles couple preferentially to the second generation Standard Model particles @LDMX:2018cma. Unlike electrons, muons experience reduced bremsstrahlung energy loss when traversing matter, allowing for deeper penetration and potentially increasing interaction rates with a dark sector mediator. This property makes muons particularly well-suited for probing dark matter candidates in a slightly higher mass range than what is currently accessible with electron beams.

Adding to these, muons also have several experimental advantages compared to those of electrons. The bremmstrahlung background processes are suppressed in muonic beams by a factor of around $(m_e/m_(mu))^2 approx 2dot 10^(-5)$. This is a crucial advantage because the production of a single neutral hadronic states from hard bremmstrahlung photons is the most difficult background process to be vetoed by the LDMX calorimetry @LDMX:2018cma. Muon beams reduce this background by a huge factor. Furthermore, a percent level momentum resolution is possible with the target placed in a magnetic field, when using muon beams. These factors promise an increased sensitivity of the experimental results, compared to using electron beams.

= Objectives
This project aims to investigate the feasibility of adapting the LDMX framework to utilize muon beams, a modification that could significantly broaden the experiment’s physics reach, as explained above.  The ability to generate an intense and well-characterized muon beam is therefore critical for testing this concept.

One promising method is to directly generate muons in electron-fixed target collisions. When a high-energy electron beam strikes a dense material such as tungsten, it produces pairs of charged muons. While this is the most straightforward way of muon-beam production inspired from the LDMX setup, we also aim to explore other ways of muon production and access their feasibility constraints in search of the most efficient and well-suited production method. Another possibility would be the production of muons through secondary processes: the electron-fixed target collisions can produce kaons and pions which can subsequently decay into muons.

A key challenge in implementing this muon-beam-based approach is efficient muon production. For comparison, a 4 GeV electron beam has a muon production rate of only around $10^(-6)$ when using the LDMX fixed target @LDMX:2018cma. Indeed, muons lose much energy compared to electrons when penetrating through targets of same radiation lengths @M3:2018. Optimizing this muon yield requires a careful study of the target material’s geometry and composition. The goal of this project is to model and simulate the production of muons from electron-target collisions using _Geant4_, a widely used particle physics simulation toolkit. By analyzing different configurations of the tungsten target, we aim to determine the optimal setup that maximizes muon production while maintaining experimental feasibility.

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
